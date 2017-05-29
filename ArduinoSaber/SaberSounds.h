#pragma once
#include "Arduino.h"


namespace SaberSound {

	typedef struct SaberSound
	{
		SaberSound(unsigned int address, unsigned long duration) : address(address), duration(duration) {}
		unsigned int address;
		unsigned long duration;
	}  SaberSound;

	const SaberSound BOOT_SOUND(18, 703);
	const SaberSound POWER_ON_SOUND(1, 1718);
	const SaberSound POWER_OFF_SOUND(2, 636);
	const SaberSound IDLE_SOUND(0, 2020);
	const SaberSound STRIKE_SOUNDS[3] = { SaberSound(11, 691) , SaberSound(12, 543), SaberSound(13, 581) };
	const SaberSound HIT_SOUNDS[4] = { SaberSound(14,1074),SaberSound(15,1123), SaberSound(16,1280), SaberSound(17,853) };
	const SaberSound SWING_SOUNDS[8] = {
		SaberSound(3,508),
		SaberSound(4,641),
		SaberSound(5,984),
		SaberSound(6,2029),
		SaberSound(7,543),
		SaberSound(8,581),
		SaberSound(9, 1231),
		SaberSound(10, 540),
	};

	/*
		Function to return a random Swing sound
	*/
	SaberSound SWING_SOUND();

	/*
		Function to return a random HIT_SOUND
	*/
	SaberSound HIT_SOUND();

	/*
		Function to return a random STRIKE_SOUND
	*/
	SaberSound STRIKE_SOUND();

} // End of SaberSound namespace