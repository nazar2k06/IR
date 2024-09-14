/*
 * Library: IR
 *
 * Description: Short library for ir module.
 * Short library that recognizes the pressing or holding of the infrared remote control button,
 * returns the unique code of this button.
 *
 * Author: Vereshchynskyi Nazar
 * Email: verechnazar12@gmail.com
 * Version: 1.0.0
 * Date: 18.06.2024
 */

#include "IR.h"

/* --- constuctor --- */
IR::IR() {
	keycode = 0;
	bits_counter = 0;

	end_parse_time = 0;
	last_tick_time = 0;

	memset(&flags, 0, sizeof(flags));
}

/* --- if is click --- */
uint32_t IR::isClick(uint32_t keycode, bool save_flag) {
	flagsTick();

	if (flags.clicked) {
		flags.clicked = (!save_flag) ? false : flags.clicked;
		bits_counter = 0;

		return (!keycode) ? this->keycode : (this->keycode == keycode) * this->keycode;
	}

	return 0;
}

/* --- if is holded --- */
uint32_t IR::isHolded(uint32_t keycode, bool save_flag) {
	flagsTick();

	if (flags.holded) {
		flags.holded = (!save_flag) ? false : flags.holded;

		return (!keycode) ? this->keycode : (this->keycode == keycode) * this->keycode;
	}

	return 0;
}

/* --- if is holding --- */
uint32_t IR::isHolding(uint32_t keycode) {
	flagsTick();

	if (flags.holding) {
		return (!keycode) ? this->keycode : (this->keycode == keycode) * this->keycode;
	}

	return 0;
}


/* --- function for processing button information --- */
void IR::flagsTick() {
	uint32_t time_delta = micros() - end_parse_time;

	if (bits_counter == 32) {
		if (!flags.holded && !flags.holding && time_delta > TIME_IGNORE + TIME_HOLD_LISTENING) {
			flags.clicked = true;
		}

		time_delta = micros() - last_tick_time;

		if (flags.holding && time_delta > TIME_HOLD_LISTENING) {
			flags.holding = false;
			bits_counter = 0;
		}
	}
}

/* --- function for button processing, call in interrupt (falling)! --- */
void IR::tick() {
	uint32_t time_delta = micros() - last_tick_time;
	last_tick_time = micros();

	if (bits_counter == 32) {
		time_delta = micros() - end_parse_time;

		if (time_delta >= TIME_IGNORE && time_delta <= TIME_IGNORE + TIME_HOLD_LISTENING && !flags.holding) {
			flags.holded = true;
			flags.holding = true;
		}

		return;
	}

	bits_counter++;
	if (bits_counter == 32) {
		end_parse_time = micros();
	}

	if (time_delta > 3000) {
		keycode = 0;
		bits_counter = 1;

		memset(&flags, 0, sizeof(flags));
	}
	if (bits_counter > 8) {
		if (time_delta > 1500) {
			keycode++;
		}
		keycode <<= 1;
	}
}