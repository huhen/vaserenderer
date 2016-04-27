#pragma once

using namespace System;
using namespace System::IO;

#include "../Render32/Render32.h"

namespace InteropRender32 {
	public ref class TextureHelper
	{
	public:
		static void LoadTexture(Stream^ textureData);
		static void RenderTexture(int textureId, array<float>^ vertextArray);
		static void RenderTextureWithoutBinding(int textureId, array<float>^ vertextArray, float opacity);//opacity = 1.0f
	};
}
