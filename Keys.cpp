#include "Keys.h"

Keys::Keys(const KEYCODE k) : key(k), prev(0) {}

const KEYSTATE Keys::state() {
	if (GetAsyncKeyState(key) == 0 && prev == 0) {
		prev = 0;
		return NON_PRESSED;
	}
	else if (GetAsyncKeyState(key) < 0 && prev == 0) {
		prev = 1;
		return PRESSED;
	}
	else if (GetAsyncKeyState(key) < 0 && prev == 1) {
		prev = 1;
		return HOLD;
	}
	else if (GetAsyncKeyState(key) == 0 && prev == 1) {
		prev = 0;
		return RELEASED;
	}

}