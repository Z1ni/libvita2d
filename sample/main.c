/*
 * Copyright (c) 2015 Sergi Granell (xerpi)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

// Symbol of the image.png file
extern unsigned char _binary_image_png_start;

int main()
{
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

	vita2d_pgf *pgf = vita2d_load_default_pgf();

	// Load the statically compiled image.png file
	vita2d_texture *image = vita2d_load_PNG_buffer(&_binary_image_png_start);

	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));

	float rad = 0.0f;

	while (1) {
		sceCtrlPeekBufferPositive(0, &pad, 1);

		if (pad.buttons & SCE_CTRL_START)
			break;

		vita2d_start_drawing();
		vita2d_clear_screen();

		vita2d_draw_rectangle(20, 20, 400, 250, RGBA8(255, 0, 0, 255));
		vita2d_draw_rectangle(680, 350, 100, 150, RGBA8(0, 0, 255, 255));
		vita2d_draw_fill_circle(200, 420, 100, RGBA8(0, 255,0 ,255));

		vita2d_draw_texture_rotate(image, 940/2, 544/2, rad);

		vita2d_draw_line(500, 30, 800, 300, RGBA8(255, 0, 255, 255));

		vita2d_pgf_draw_text(pgf, 700, 30, RGBA8(0,255,0,255), 1.0f, "PGF Font sample!");

		vita2d_end_drawing();
		vita2d_swap_buffers();

		rad += 0.1f;
	}

	vita2d_wait_rendering_done();
	vita2d_free_texture(image);
	vita2d_free_pgf(pgf);
	vita2d_fini();

	sceKernelExitProcess(0);
	return 0;
}
