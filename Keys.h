#include <Windows.h>

#ifndef KEYS
#define KEYS
typedef
enum KEYCODE {
	// SPECIAL KEYS
	K_BACKSPACE		= 0x08,
	K_TAB			= 0x09,
	K_Enter			= 0x0D,
	K_SHIFT			= 0x10,
	K_CTRL			= 0x11,
	K_ALT			= 0x12,
	K_CAPS			= 0x14,
	K_ESC			= 0x1B,
	K_SPACEBAR		= 0x20,
	K_PAGE_UP		= 0x21,
	K_PAGE_DOWN		= 0x22,
	K_END			= 0x23,
	K_HOME			= 0x24,
	K_LEFT_ARROW	= 0x25,
	K_UP_ARROW		= 0x26,
	K_RIGHT_ARROW	= 0x27,
	K_DOWN_ARROW	= 0x28,
	K_SELECT		= 0x29,
	K_PRINT			= 0x2A,
	K_PRNT_SCREEN	= 0x2C,
	K_INSERT		= 0x2D,
	K_DEL			= 0x2E,
	K_LWIN			= 0x5B,
	K_RWIN			= 0x5C,
	K_APPS			= 0x5D,
	K_NUMLOCK		= 0x90,
	K_SCROLL		= 0x91,
	K_LSHIFT		= 0xA0,
	K_RSHIFT		= 0xA1,
	K_LCTRL			= 0xA2,
	K_RCTRL			= 0xA3,
	K_LMENU			= 0xA4,
	K_RMENU			= 0xA5,

	//NUMBERS
	K_0				= 0x30,
	K_1				= 0x31,
	K_2				= 0x32,
	K_3				= 0x33,
	K_4				= 0x34,
	K_5				= 0x35,
	K_6				= 0x36,
	K_7				= 0x37,
	K_8				= 0x38,
	K_9				= 0x39,

	// LETTERS
	K_A				= 0x41,
	K_B				= 0x42,
	K_C				= 0x43,
	K_D				= 0x44,
	K_E				= 0x45,
	K_F				= 0x46,
	K_G				= 0x47,
	K_H				= 0x48,
	K_I				= 0x49,
	K_J				= 0x4A,
	K_K				= 0x4B,
	K_L				= 0x4C,
	K_M				= 0x4D,
	K_N				= 0x4E,
	K_O				= 0x4F,
	K_P				= 0x50,
	K_Q				= 0x51,
	K_R				= 0x52,
	K_S				= 0x53,
	K_T				= 0x54,
	K_U				= 0x55,
	K_V				= 0x56,
	K_W				= 0x57,
	K_X				= 0x58,
	K_Y				= 0x59,
	K_Z				= 0x5A,

	// NUMPAD KEYS
	K_NUMPAD0		= 0x60,
	K_NUMPAD1		= 0x61,
	K_NUMPAD2		= 0x62,
	K_NUMPAD3		= 0x63,
	K_NUMPAD4		= 0x64,
	K_NUMPAD5		= 0x65,
	K_NUMPAD6		= 0x66,
	K_NUMPAD7		= 0x67,
	K_NUMPAD8		= 0x68,
	K_NUMPAD9		= 0x69,
	K_MULTIPLY		= 0x6A,
	K_ADD			= 0x6B,
	K_SEPARATOR		= 0x6C,
	K_SUBTRACT		= 0x6D,
	K_DEC			= 0x6E,
	K_DIVIDE		= 0x6F,

	// FUNCTION KEYS
	K_F1			= 0x70,
	K_F2			= 0x71,
	K_F3			= 0x72,
	K_F4			= 0x73,
	K_F5			= 0x74,
	K_F6			= 0x75,
	K_F7			= 0x76,
	K_F8			= 0x77,
	K_F9			= 0x78, 
	K_F10			= 0x79,
	K_F11			= 0x7A,
	K_F12			= 0x7B,
	K_F13			= 0x7C,
	K_F14			= 0x7D,
	K_F15			= 0x7E,
	K_F16			= 0x7F,
	K_F17			= 0x80,
	K_F18			= 0x81,
	K_F19			= 0x82,
	K_F20			= 0x83,
	K_F21			= 0x84,
	K_F22			= 0x85,
	K_F23			= 0x86,
	K_F24			= 0x87,
}	KEYCODE;

typedef
enum KEYSTATE {
	NON_PRESSED,
	PRESSED,
	HOLD,
	RELEASED,

}	KEYSTATE;

class Keys
{
private:
	int prev;
	const int key;

public:
	Keys(const KEYCODE k);

	const KEYSTATE state();
};
#endif // !KEYS

