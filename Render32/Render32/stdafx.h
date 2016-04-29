// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // »сключите редко используемые компоненты из заголовков Windows
// ‘айлы заголовков Windows:
#include <windows.h>

#include <gl/GL.h>
#include <gl/glext.h>

PFNGLUSEPROGRAMPROC extern glUseProgram;
PFNGLCREATESHADERPROC extern glCreateShader;
PFNGLCREATEPROGRAMPROC extern glCreateProgram;
PFNGLSHADERSOURCEPROC extern glShaderSource;
PFNGLCOMPILESHADERPROC extern glCompileShader;
PFNGLATTACHSHADERPROC extern glAttachShader;
PFNGLLINKPROGRAMPROC extern glLinkProgram;
PFNGLDELETEPROGRAMPROC extern glDeleteProgram;
PFNGLGETSHADERIVPROC extern glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC extern glGetShaderInfoLog;
PFNGLGENBUFFERSPROC extern glGenBuffers;
PFNGLBINDBUFFERPROC extern glBindBuffer;
PFNGLBUFFERDATAPROC extern glBufferData;
PFNGLDELETEBUFFERSPROC extern glDeleteBuffers;

// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
