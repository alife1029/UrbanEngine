#include "BaseViewport.h"

#include <glad/glad.h>

namespace UrbanEngine
{
	int BaseViewport::s_X = 0;
	int BaseViewport::s_Y = 0;
	int BaseViewport::s_Width = 0;
	int BaseViewport::s_Height = 0;
	float BaseViewport::s_AspectRatio = 1.0f;

	void BaseViewport::UpdateAsFillViewport(Window* target)
	{
		s_X = 0;
		s_Y = 0;
		s_Width = target->Width();
		s_Height = target->Height();
		s_AspectRatio = static_cast<float>(s_Width) / static_cast<float>(s_Height);
		
		Update(target->Gfx());
	}

	void BaseViewport::UpdateAsFitViewport(Window* target, float aspectRatio)
	{
		float windowAspect = static_cast<float>(target->Width()) / static_cast<float>(target->Height());

		if (windowAspect > aspectRatio)
		{
			s_Width = static_cast<int>(target->Height() * aspectRatio);
			s_Height = target->Height();
			s_X = static_cast<int>((static_cast<float>(target->Width()) - s_Width) / 2.0f);
			s_Y = 0;
		}
		else
		{
			s_Width = target->Width();
			s_Height = static_cast<int>(target->Width() / aspectRatio);
			s_X = 0;
			s_Y = static_cast<int>((target->Height() - s_Height) / 2.0f);
		}

		s_AspectRatio = static_cast<float>(s_Width) / static_cast<float>(s_Height);

		Update(target->Gfx());
	}

	void BaseViewport::Update(Graphics* gfx)
	{
		switch (gfx->GetRendererAPI())
		{
		case Graphics::API::D3D11:
			// TODO: Update D3D11 Viewport
			break;
		case Graphics::API::GL460:
			glViewport(s_X, s_Y, s_Width, s_Height);
			break;
		case Graphics::API::GLES30:
			// TODO: Update GLES Viewport
			break;
		case Graphics::API::NONE:
			// TODO: You can throw an exception
			break;
		}
	}

	int BaseViewport::GetX()
	{
		return s_X;
	}
	int BaseViewport::GetY()
	{
		return s_Y;
	}
	int BaseViewport::GetWidth()
	{
		return s_Width;
	}
	int BaseViewport::GetHeight()
	{
		return s_Height;
	}
	float BaseViewport::GetAspectRatio()
	{
		return s_AspectRatio;
	}
}
