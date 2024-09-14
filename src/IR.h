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

#ifndef _IR_H
#define _IR_H

#include <Arduino.h>

/* --- time to ignore signals after pressing the button --- */
#define TIME_IGNORE 60000

/* --- the waiting time for the signal which will mean that the button is holded --- */
#define TIME_HOLD_LISTENING 100000

/* --- last action flags above the button --- */
struct ir_flags {
	bool clicked;
	bool holded;
	bool holding;
};

/* --- main class --- */
class IR {
public:
	IR();

	uint32_t isClick(uint32_t keycode = 0, bool save_flag = false);
	uint32_t isHolded(uint32_t keycode = 0, bool save_flag = false);
	uint32_t isHolding(uint32_t keycode = 0);

	void flagsTick();
	void tick();

private:
	uint32_t keycode;
	uint8_t bits_counter;

	uint32_t end_parse_time;
	uint32_t last_tick_time;

	ir_flags flags;
};

#endif