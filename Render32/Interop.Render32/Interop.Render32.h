// Interop.Render32.h

#pragma once

#pragma unmanaged
#include "../Render32/Render32.h"
#pragma managed

#include <windows.h>
#include <vcclr.h>
#using <System.dll>

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
		void MethodB(array<float>^ arr) {
			pin_ptr<float> pUnmanagedArr = &arr[0];
			m_Impl->MethodB(pUnmanagedArr, arr->Length);
		}

	private:
		UnmanagedClass * m_Impl;
	};
}
