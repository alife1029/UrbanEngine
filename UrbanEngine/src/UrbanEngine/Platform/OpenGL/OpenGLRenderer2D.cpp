#include "OpenGLRenderer2D.h"
#include "OpenGLShader.h"
#include "OpenGLGraphics.h"

#include <glad/glad.h>

#include <cstdint>

#define QUAD_PER_BATCH 1000

namespace UrbanEngine
{
	struct Vertex
	{
		glm::vec2 Position;
		glm::vec4 Color;
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

		OpenGLShader*	ShaderProgram = nullptr;
		
		glm::mat4		ViewProj{ 1.0f };
	};

	static RendererData s_Data = RendererData();

	void OpenGLRenderer2D::Initialize(Graphics* gfx)
	{
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
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

		// Unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Delete indices array
		delete[] indices;
	}
	
	void OpenGLRenderer2D::Shutdown()
	{
		glDeleteVertexArrays(1, &s_Data.VAO);
		glDeleteBuffers(1, &s_Data.VBO);
		glDeleteBuffers(1, &s_Data.EBO);

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

		// Update uniform variable values
		s_Data.ShaderProgram->SetUniformMat4("u_ViewProj", s_Data.ViewProj);

		glBindVertexArray(s_Data.VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.EBO);
		
		s_Data.Gfx->DrawIndexed(s_Data.IndexCount);

		s_Data.IndexCount = 0;
	}
	
	void OpenGLRenderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		if (s_Data.IndexCount >= QUAD_PER_BATCH)
		{
			EndFrame();
			BeginFrame(s_Data.ViewProj);
		}

		// Initial vertex positions
		glm::vec4 vertexPoses[] = {
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f,  0.5f, 0.0f, 1.0f },
			{ -0.5f,  0.5f, 0.0f, 1.0f }
		};
		
		// Transform vertex poses
		for (auto vertexPos : vertexPoses)
		{
			glm::vec2 pos = transform * vertexPos;
			s_Data.QuadBufferPtr->Position = pos;
			s_Data.QuadBufferPtr->Color = color;
			++s_Data.QuadBufferPtr;
		}

		s_Data.IndexCount += 6;
	}
}
