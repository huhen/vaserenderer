// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
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

// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
