#include <windows.h>
#include <gl/GL.h>

#include "includes/renderer.h"
#include "includes/backend.h"

namespace VASEr
{
	void renderer::init()
	{
	}

	void renderer::before()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glDisableClientState(GL_EDGE_FLAG_ARRAY);
		//glDisableClientState(GL_FOG_COORD_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		//glDisableClientState(GL_SECONDARY_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void renderer::after()
	{
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisable(GL_BLEND);
	}

	Image renderer::get_image()
	{
		int res[4];
		glGetIntegerv(GL_VIEWPORT, res);
		Image im = { 0 };
		im.width = res[2];
		im.height = res[3];
		im.buf = (unsigned char*)malloc(im.width*im.height * 4);
		if (!im.buf)
			return im;
		glReadPixels(0, 0, im.width, im.height, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)im.buf);
		//flip horizontally
		for (int i = 0; i < im.height / 2; i++)
			for (int j = 0; j < im.width; j++)
				VASErin::swap_pixel(im.buf, im.width, j, i, j, im.height - i - 1);
		return im;
	}
}
