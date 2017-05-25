#pragma once
#include "Arduino.h"

namespace Saber {

	const long POWER_ON_SOUND_TIME = 1718l;
	const long POWER_OFF_SOUND_TIME = 616l;

	// Enum that maps to sounds flashed into the sound board
	enum SaberSounds {
		IDLE = 0,
		ON = 1,
		OFF = 2,
		SWING1 = 3,
		SWING2 = 4,
		SWING3 = 5,
		SWING4 = 6,
		SWING5 = 7,
		SWING6 = 8,
		SWING7 = 9,
		SWING8 = 10,
		STRIKE1 = 11,
		STRIKE2 = 12,
		STRIKE3 = 13,
		HIT1 = 14,
		HIT2 = 15,
		HIT3 = 16,
		HIT4 = 17,
		STARTUP = 18
	};

	// The following give constants to allow the saber to chose one for a particular action
	const unsigned int MIN_SWING = 3;
	const unsigned int MAX_SWING = 10;
	const unsigned int MIN_STRIKE = 11;
	const unsigned int MAX_STRIKE = 13;
	const unsigned int MIN_HIT = 14;
	const unsigned int MAX_HIT = 17;

	// Used for comparison to see if the sound board is busy - Pin goes low if board is busy
	const int BUSY_VALUE = 0;

	class SaberSound
	{
	public:
		SaberSound(byte dataPin, byte busyPin, byte resetPin);
		~SaberSound();

		bool isBusy() const;
		void playSwingSound() const;
		void playHitSound() const;
		void playStrikeSound() const;
		void playSound(int sound) const;
		void reset() const;

	private:
		const byte _dataPin;
		const byte _busyPin;
		const byte _resetPin;
	};
} // End namespace Saber
