//
// Created by 14419 on 25-8-13.
//
#include "draw.h"

static uint32_t g_xres, g_yres, g_bpp; // 屏幕分辨率
static uint8_t *g_framebuffer;  // 指向实际OLED的缓冲区，所有绘图都写入这个地址

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


/**
 * @brief 在帧缓冲区 buff 的指定位置写入一个字节值，用于控制 OLED 屏幕上 8 像
 * @param buff 指向帧缓冲区的指针
 * @param x 水平像素坐标
 * @param y 垂直像素坐标
 * @param val 要写入的字节值
 */
static void setBuffByte(uint8_t* buff, uint8_t x, uint8_t y, uint8_t val)//, byte colour)
{
	// 帧缓冲区的字节索引 y / 8当前page,
	const uint16_t pos = x + (y / 8) * FRAME_WIDTH;
	buff[pos] |= val;
}

/*定义字体集合，大小是 5 * 7*/
const uint8_t smallFont[][5]  = {
	CHARACTER_SET
  };

/**
 * @brief 函数逐字符绘制字符串
 * @param string 指向要绘制的字符串
 * @param invert 是否反转模式
 * @param x 起始坐标x
 * @param y 起始坐标y
 */
void draw_string(const char* string, bool invert, uint8_t x, uint8_t y)
{
	uint8_t charCount = 0; // 记录档期那字符数

	while(*string) // 遍历字符串（ASCII值），直到遇到空字符
	{
		const char c = *string - 0x20; // 映射字体数组索引
		const uint8_t xx = x + (charCount*7); // 计算当前字符的水平绘制位置（每个字符占用 7 像素宽度）
		// 调用 `draw_bitmap` 函数绘制单个字符的位图
		draw_bitmap(xx, y, smallFont[(uint8_t)c], SMALLFONT_WIDTH, SMALLFONT_HEIGHT, invert, 0);
		if(invert) // 额外绘制垂直线条，增强反转效果
		{
			if(xx > 0)
				setBuffByte(g_framebuffer, xx-1, y, 0xFF);//, WHITE);
			if(xx < FRAME_WIDTH - 5)
				setBuffByte(g_framebuffer, xx+5, y, 0xFF);//, WHITE);
		}
		string++;
		charCount++;
	}
}