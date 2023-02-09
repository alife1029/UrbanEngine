#include "OpenGLRenderer2D.h"
#include "OpenGLShader.h"
#include "OpenGLGraphics.h"

#include <glad/glad.h>

#include <cstdint>

static constexpr size_t QUAD_PER_BATCH = 1000;
static int MAX_TEXTURES = 0;

namespace UrbanEngine
{
	struct Vertex
	{
		glm::vec2 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoordinate;
		float TextureIndex;
	};

	struct RendererData
	{
		OpenGLGraphics*	Gfx = nullptr;

		GLuint			VBO = 0;
		GLuint			VAO = 0;
		GLuint			EBO = 0;
		
		uint32_t		IndexCount = 0;

		Vertex*			QuadBuffer = nullptr;
		Vertex*			QuadBufferPtr = nullptr;

		uint32_t*		TextureSlots = nullptr;
		uint32_t		TextureSlotIndex = 0;

		OpenGLShader*	ShaderProgram = nullptr;
		
		glm::mat4		ViewProj{ 1.0f };
	};

	static RendererData s_Data = RendererData();

	void OpenGLRenderer2D::Initialize(Graphics* gfx)
	{
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MAX_TEXTURES);

		s_Data.Gfx = reinterpret_cast<OpenGLGraphics*>(gfx);
		s_Data.ShaderProgram = new OpenGLShader(gfx, "shaders/Solid2DVS.glsl", "shaders/Solid2DFS.glsl");
		
		s_Data.QuadBuffer = new Vertex[QUAD_PER_BATCH];

		// Calculate indices
		const size_t indexCount = QUAD_PER_BATCH * 6;
		GLushort* indices = new GLushort[indexCount];
		uint16_t offset = 0;
		for (size_t i = 0; i < indexCount; i += 6)
		{
			indices[i] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset;
			indices[i + 4] = offset + 2;
			indices[i + 5] = offset + 3;
			offset += 4;
		}
		
		// Generate OpenGL buffers
		glCreateVertexArrays(1, &s_Data.VAO);
		glCreateBuffers(1, &s_Data.VBO);
		glCreateBuffers(1, &s_Data.EBO);

		// Bind OpenGL buffers
		glBindVertexArray(s_Data.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.EBO);

		// Load OpenGL buffer datas
		glBufferData(GL_ARRAY_BUFFER, QUAD_PER_BATCH * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLushort), indices, GL_STATIC_DRAW);

		// Vertex attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureCoordinate));
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureIndex));

		// Unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Delete indices array
		delete[] indices;

		// Texture slots initialization
		s_Data.TextureSlots = new uint32_t[MAX_TEXTURES];
		for (size_t i = 0; i < MAX_TEXTURES; i++)
			s_Data.TextureSlots[i] = 0;
		s_Data.TextureSlotIndex = 0;
	}
	
	void OpenGLRenderer2D::Shutdown()
	{
		glDeleteVertexArrays(1, &s_Data.VAO);
		glDeleteBuffers(1, &s_Data.VBO);
		glDeleteBuffers(1, &s_Data.EBO);

		delete[] s_Data.TextureSlots;
		delete[] s_Data.QuadBuffer;
		delete s_Data.ShaderProgram;
	}
	
	void OpenGLRenderer2D::BeginFrame(const glm::mat4& viewProject)
	{
		s_Data.QuadBufferPtr = s_Data.QuadBuffer;
		s_Data.ViewProj = viewProject;
	}
	
	void OpenGLRenderer2D::EndFrame()
	{
		// Load vertex datas to the VRAM
		GLsizeiptr size = (uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, (const void*)s_Data.QuadBuffer);

		// Activate the shader program
		s_Data.ShaderProgram->Bind();

		// Bind texture layers
		int* samplers = new int[s_Data.TextureSlotIndex];
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			glBindTextureUnit(i, s_Data.TextureSlots[i]);
			samplers[i] = i;
		}

		// Update uniform variable values
		s_Data.ShaderProgram->SetUniformMatrix4("u_ViewProj", s_Data.ViewProj);
		s_Data.ShaderProgram->SetUniformIntArray("u_Samplers", samplers, s_Data.TextureSlotIndex);

		glBindVertexArray(s_Data.VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.EBO);
		
		s_Data.Gfx->DrawIndexed(s_Data.IndexCount);

		s_Data.IndexCount = 0;
		s_Data.TextureSlotIndex = 0;

		delete[] samplers;
	}
	
	void OpenGLRenderer2D::DrawQuad(OpenGLTexture2D* texture, const glm::mat4& transform, const glm::vec4& color)
	{
		if (s_Data.IndexCount >= QUAD_PER_BATCH)
		{
			EndFrame();
			BeginFrame(s_Data.ViewProj);
		}

		// Is the texture has used in the current batch?
		float texIndex = -1.0f;
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (s_Data.TextureSlots[i] == texture->GetID())
			{
				texIndex = (float)i;
				break;
			}
		}

		// If not used, add the id of this texture to the texture slots array
		if (texIndex == -1.0f)
		{
			if (s_Data.TextureSlotIndex >= MAX_TEXTURES - 1)
			{
				EndFrame();
				BeginFrame(s_Data.ViewProj);
			}

			texIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture->GetID();
			++s_Data.TextureSlotIndex;
		}

		// Initial vertex datas (non-transformed)
		float qHW = texture->Width() / 2.0f / texture->PixelPerUnit();	// Quad half width
		float qHH = texture->Height() / 2.0f / texture->PixelPerUnit();	// Quad half height
		glm::vec4 vertexPoses[] = {
			{ -qHW, -qHH, 0.0f, 1.0f },
			{  qHW, -qHH, 0.0f, 1.0f },
			{  qHW,  qHH, 0.0f, 1.0f },
			{ -qHW,  qHH, 0.0f, 1.0f }
		};
		glm::vec2 texCoords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};
		
		// Calculate each vertex
		for (size_t i = 0; i < 4; i++)
		{
			s_Data.QuadBufferPtr->Position = transform * vertexPoses[i];
			s_Data.QuadBufferPtr->Color = color;
			s_Data.QuadBufferPtr->TextureCoordinate = texCoords[i];
			s_Data.QuadBufferPtr->TextureIndex = texIndex;
			++s_Data.QuadBufferPtr;
		}

		s_Data.IndexCount += 6;
	}
}
