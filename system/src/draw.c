//
// Created by 14419 on 25-8-13.
//
#include "draw.h"

static uint32_t g_xres, g_yres, g_bpp; // 屏幕分辨率
static uint8_t *g_framebuffer;  // 指向实际OLED的缓冲区，所有绘图都写入这个地址

#define FRAME_HEIGHT 64
#define FRAME_WIDTH 128
/**
 * @brief 从特定内存数据读取位图像素数据
 * @param loc 指向位图数据的某个位置的指针（Flash or RAM)
 * @param invert flag值，是否需要反转像素
 * @retval 返回8个像素的数据
 */
uint8_t readPixels(const uint8_t* loc, bool invert)
{
	uint8_t pixels = *loc; // 直接解引用，无需 pgm_read_uint8_t
	return invert ? ~pixels : pixels;
}

/**
 * @brief 从显示驱动中获取framebuffer地址，并保存参数
 */
void draw_init() {
    g_framebuffer = (uint8_t *)OLED_GetFrameBuffer(&g_xres, &g_yres, &g_bpp);
}

/**
 * @brief 将framebuffer内容刷新到实际屏幕中
 *         清空内部framebuffer（为下次绘制做准备）
 */
void draw_end() {
    OLED_ShowFrame();
    OLED_NewFrame();

}

void draw_bitmap(uint8_t x, uint8_t yy, const uint8_t* bitmap, uint8_t w, uint8_t h, bool invert, uint8_t offsetY)
{
	/*一、 计算绘制位置*/
	// yy += animation_offsetY(); // 获取动画偏移
	yy += 0; // 直接禁用了动画效果
	uint8_t y = yy - offsetY; // 调整起始 Y 坐标
	uint8_t h2 = h / 8; // 计算位图高度的块数;
	uint8_t pixelOffset = (y % 8); // 计算像素偏移
	uint8_t thing3 = (yy+h); // 计算位图底部

	/*一、 按 8 像素块循环处理*/
	LOOP(h2, hh)
	{
		// 计算当前块的 Y 范围
		uint8_t hhh = (hh * 8) + y; // 当前块的起始 Y 坐标
		uint8_t hhhh = hhh + 8; // 当前块的结束 Y 坐标

		// **裁剪检查**
		if(offsetY && (hhhh < yy || hhhh > FRAME_HEIGHT || hhh > thing3))
			continue;

		//
		uint8_t offsetMask = 0xFF; // 决定哪些像素有效（0xFF 表示全选）
		if(offsetY)
		{
			if(hhh < yy)
				offsetMask = (0xFF<<(yy-hhh));
			else if(hhhh > thing3)
				offsetMask = (0xFF>>(hhhh-thing3));
		}

		/* 计算显存位置和位图数据 */
		uint16_t aa = ((hhh / 8) * FRAME_WIDTH); // 显存偏移

		const uint8_t* b = bitmap + (hh*w); // 位图数据指针

		/*函数根据像素是否对齐页面边界，分两种情况处理*/
		// If() outside of loop makes it faster (doesn't have to keep re-evaluating it)
		// Downside is code duplication
		if(!pixelOffset && hhh < FRAME_HEIGHT)
		{
			//
			LOOP(w, ww)
			{
				// Workout X co-ordinate in frame buffer to place next 8 pixels
				uint8_t xx = ww + x;

				// Stop if X co-ordinate is outside the frame
				if(xx >= FRAME_WIDTH)
					continue;

				// Read pixels
				uint8_t pixels = readPixels(b + ww, invert) & offsetMask;

				g_framebuffer[xx + aa] |= pixels;

				//setBuffuint8_t(buff, xx, hhh, pixels, colour);
			}
		}
		else
		{
			uint16_t aaa = ((hhhh / 8) * FRAME_WIDTH);

			//
			LOOP(w, ww)
			{
				// Workout X co-ordinate in frame buffer to place next 8 pixels
				uint8_t xx = ww + x;

				// Stop if X co-ordinate is outside the frame
				if(xx >= FRAME_WIDTH)
					continue;

				// Read pixels
				uint8_t pixels = readPixels(b + ww, invert) & offsetMask;

				//
				if(hhh < FRAME_HEIGHT)
					g_framebuffer[xx + aa] |= pixels << pixelOffset;
					//setBuffuint8_t(buff, xx, hhh, pixels << pixelOffset, colour);

				//
				if(hhhh < FRAME_HEIGHT)
					g_framebuffer[xx + aaa] |= pixels >> (8 - pixelOffset);
					//setBuffuint8_t(buff, xx, hhhh, pixels >> (8 - pixelOffset), colour);
			}
		}
	}
}
