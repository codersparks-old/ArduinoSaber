#include "SaberSound.h"
#include "Arduino.h"


Saber::SaberSound::SaberSound(byte dataPin, byte busyPin, byte resetPin) : _dataPin(dataPin), _busyPin(busyPin), _resetPin(resetPin)
{
	pinMode(_dataPin, OUTPUT);
	pinMode(_resetPin, OUTPUT);

	digitalWrite(_resetPin, HIGH);
	pinMode(_busyPin, INPUT_PULLUP);
}

Saber::SaberSound::~SaberSound()
{
}

bool Saber::SaberSound::isBusy() const
{
	int busyVal = digitalRead(_busyPin);

	if (busyVal == BUSY_VALUE) {
		return true;
	}
	else {
		return false;
	}
}

void Saber::SaberSound::playSound(SaberSounds sound) const
{

	digitalWrite(_dataPin, LOW);	// We need to ensure that the chip is woken up from sleep mode
	delay(5);

	for (int i = 0; i < 8; i++) {

		if (bitRead(sound, i)) { // Read each bit of the sound to be played

			digitalWrite(_dataPin, 1);
			delayMicroseconds(400);
			digitalWrite(_dataPin, 0); // 2:1 high/low indicates high
			delayMicroseconds(200);
		}
		else {
			digitalWrite(_dataPin, 1);
			delayMicroseconds(200);
			digitalWrite(_dataPin, 0);
			delayMicroseconds(400);
		}
	}

	digitalWrite(_dataPin, 1);

	while (!this->isBusy()) {}

}
