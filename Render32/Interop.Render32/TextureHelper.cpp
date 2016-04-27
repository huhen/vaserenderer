#include "stdafx.h"
#include "TextureHelper.h"

using namespace System;
using namespace System::IO;


namespace InteropRender32 {

	void TextureHelper::LoadTexture(Stream^ textureData)
	{
		throw gcnew System::NotImplementedException();
	}

	void TextureHelper::RenderTexture(int textureId, array<float>^ vertextArray)
	{
		throw gcnew System::NotImplementedException();
	}

	void TextureHelper::RenderTextureWithoutBinding(int textureId, array<float>^ vertextArray, float opacity)
	{
		throw gcnew System::NotImplementedException();
	}
}
