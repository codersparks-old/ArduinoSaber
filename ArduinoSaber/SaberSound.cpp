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

void Saber::SaberSound::playSound(int sound) const
{

	if (Serial) {
		Serial.print("Playing sound: ");
		Serial.println(sound);
	}

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

	digitalWrite(_dataPin, HIGH);

	while (!this->isBusy()) {}

}

void Saber::SaberSound::playSwingSound() const {

	// Use arduino random to pick a swing sound to play
	int sound = random(MIN_SWING, MAX_SWING);

	this->playSound(sound);
}

void Saber::SaberSound::playHitSound() const
{
	int sound = random(MIN_HIT, MAX_HIT);

	this->playSound(sound);
}

void Saber::SaberSound::playStrikeSound() const
{
	int sound = random(MIN_STRIKE, MAX_STRIKE);

	this->playSound(sound);
}

void Saber::SaberSound::reset() const
{
	digitalWrite(_resetPin, LOW);
	delay(5);
	digitalWrite(_resetPin, HIGH);
	delay(18);
}
