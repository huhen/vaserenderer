// ֳכאגםûי DLL-פאיכ.

#include "stdafx.h"

#include "Interop.Render32.h"
namespace InteropRender32
{
	void OpenGlRender::DeleteTexture(uint tId)
	{
		UnmanagedClass::DeleteTexture(tId);
	}

	void OpenGlRender::TexImage2D(int width, int heigh, IntPtr pixels)
	{
		UnmanagedClass::TexImage2D(width, heigh, pixels.ToPointer());
	}

	void OpenGlRender::DrawSimplePolyLine(array<float>^ buffer, float width, uint color)
	{
		pin_ptr<float> pUnmanagedArr = &buffer[0];
		UnmanagedClass::DrawSimplePolyLine(pUnmanagedArr, buffer->Length / 2, width, color);
	}

	void OpenGlRender::DrawSimplePoint(float x, float y, float width, uint color)
	{
		UnmanagedClass::DrawSimplePoint(x, y, width, color);
	}

	void OpenGlRender::DrawSimplePolygone(array<float>^ buffer, float width, uint color)
	{
		pin_ptr<float> pUnmanagedArr = &buffer[0];
		UnmanagedClass::DrawSimplePolygone(pUnmanagedArr, buffer->Length / 2, width, color);
	}
}
