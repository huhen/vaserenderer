// Interop.Render32.h

#pragma once

#pragma unmanaged
#include "../Render32/Render32.h"
#pragma managed

#include <windows.h>
#include <vcclr.h>
#using <System.dll>

#include "TextureHelper.h"

using namespace System;

namespace InteropRender32 {

	public ref class OpenGlRender {
	public:
		// Allocate the native object on the C++ Heap via a constructor
		OpenGlRender() : m_Impl(new UnmanagedClass) {}

		// Deallocate the native object on a destructor
		~OpenGlRender() {
			delete m_Impl;
		}

	protected:
		// Deallocate the native object on the finalizer just in case no destructor is called
		!OpenGlRender() {
			delete m_Impl;
		}


	public:
		static void DeleteTexture(uint tId);
		static uint TexImage2D(int width, int heigh, IntPtr pixels);
		static void DrawSimplePolyLine(array<float>^ buffer, float width, uint color);
		static void DrawSimplePoint(float x, float y, float width, uint color);
		static void DrawSimplePolygone(array<float>^ buffer, float width, uint color);
		static void RenderTexture(uint tId, array<float>^ vertextArray);
		static void RenderTexture(uint tId, float x, float y, float orientation, float scale, float opacity, array<float>^ vertextArray);
		static void Clear();
		static void SetupViewPort(int width, int heigh);

		void DrawFinePolyLine(array<float>^ buffer, float width, uint color);
		void DrawFinePolyLine(array<float>^ buffer, float width, uint color, uint colorC);

		void Init(IntPtr hWnd);
		void DeleteContext();
		void SwapBuffersContext();
	private:
		UnmanagedClass * m_Impl;
	};
}
