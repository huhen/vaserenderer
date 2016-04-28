// ֳכאגםûי DLL-פאיכ.

#include "stdafx.h"

#include "Interop.Render32.h"
namespace InteropRender32
{
	void OpenGlRender::SwapBuffersContext()
	{
		m_Impl->SwapBuffersContext();
	}

	void OpenGlRender::DeleteContext()
	{
		m_Impl->DeleteContext();
	}

	void OpenGlRender::Init(IntPtr hWnd)
	{
		m_Impl->Init((HWND)hWnd.ToPointer());
	}

	void OpenGlRender::DeleteTexture(uint tId)
	{
		UnmanagedClass::DeleteTexture(tId);
	}

	void OpenGlRender::Clear()
	{
		UnmanagedClass::Clear();
	}

	void OpenGlRender::SetupViewPort(int width, int heigh)
	{
		UnmanagedClass::SetupViewPort(width, heigh);
	}

	uint OpenGlRender::TexImage2D(int width, int heigh, IntPtr pixels)
	{
		return UnmanagedClass::TexImage2D(width, heigh, pixels.ToPointer());
	}

	void OpenGlRender::DrawSimplePolyLine(array<float>^ buffer, float width, uint color)
	{
		pin_ptr<float> pUnmanagedArr = &buffer[0];
		UnmanagedClass::DrawSimplePolyLine(pUnmanagedArr, buffer->Length / 2, width, color);
	}

	void OpenGlRender::DrawFinePolyLine(array<float>^ buffer, float width, uint color)
	{
		pin_ptr<float> pUnmanagedArr = &buffer[0];
		UnmanagedClass::DrawFinePolyLine(pUnmanagedArr, buffer->Length / 2, width, color);
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

	void OpenGlRender::RenderTexture(uint tId, array<float>^ vertextArray)
	{
		pin_ptr<float> pUnmanagedArr = &vertextArray[0];
		UnmanagedClass::RenderTexture(tId, pUnmanagedArr);
	}

	void OpenGlRender::RenderTexture(uint tId, float x, float y, float orientation, float scale, float opacity, array<float>^ vertextArray)
	{
		pin_ptr<float> pUnmanagedArr = &vertextArray[0];
		UnmanagedClass::RenderTexture(tId, x, y, orientation, scale, opacity, pUnmanagedArr);
	}
}
