//
// Created by 14419 on 25-8-31.
//
#include "m_display.h"
#define OPTION_COUNT	5
extern appconfig_s appConfig;
static prev_menu_s prevMenuData;

static void mSelect(void);
static void itemLoader(uint8_t);
static void setBrightness(void);
static void setInvert(void);
static void setRotate(void);
#if COMPILE_ANIMATIONS
static void setAnimations(void);
#endif
static void setMenuOptions(void);

void mDisplayOpen()
{
	setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, (STR_DISPLAYMENU));
	setMenuFuncs(nextOption, prevOption, mSelect, itemLoader);

	setPrevMenuOpen(&prevMenuData, mDisplayOpen);

	beginAnimation2(NULL);
}

static void mSelect()
{
	bool isExiting = exitSelected();
	if(isExiting)
		appconfig_save();
	setPrevMenuExit(&prevMenuData);
	doAction(exitSelected());
}

static void itemLoader(uint8_t num)
{
	UNUSED(num);
	setMenuOptions();
	addBackOption();
}

static void setBrightness()
{
 	uint8_t brightness = appConfig.brightness;
	if(brightness > 4)
		brightness = 0;
	
	brightness++;
	appConfig.brightness = brightness;
	
	uint8_t _brightness = 0;

	switch(brightness)
	{
		case 0:	_brightness = 0x01; break;
		case 1:	_brightness = 0x0f; break;
		case 2:	_brightness = 0x5f; break;
		case 3:	_brightness = 0xff; break;
	}	

	OLED_Backlight(_brightness);
}

static void setInvert()
{
	appConfig.invert = !appConfig.invert;
	
	OLED_SetColorMode(appConfig.invert);
}

static void setRotate() 
{
	if(appConfig.display180 == false)
		appConfig.display180 = true;
	else if(appConfig.display180 == true)
		appConfig.display180 = false;
	else
		appConfig.display180 = false;

	OLED_DisplayTurn_CH1116(appConfig.display180);
}

static void setLEDs() {
  appConfig.CTRL_LEDs = !appConfig.CTRL_LEDs;
	// ColorLED_Set(0x00000000);
}

#if COMPILE_ANIMATIONS
static void setAnimations()
{
	appConfig.animations = !appConfig.animations;
}
#endif

static void setMenuOptions()
{
	setMenuOption(0, (STR_BRIGHTNESS), menu_brightness[appConfig.brightness], setBrightness);
	setMenuOption(1, (STR_INVERT), menu_invert, setInvert);
	setMenuOption(2, (STR_ROTATE), menu_rotate, setRotate);
#if COMPILE_ANIMATIONS
	setMenuOption(3, (STR_ANIMATIONS), menu_anim[appConfig.animations], setAnimations);
#endif
	setMenuOption(4, (STR_LEDS), menu_LEDs[appConfig.CTRL_LEDs], setLEDs);


}