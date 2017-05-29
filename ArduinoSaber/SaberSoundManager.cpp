#include "SaberSoundManager.h"
#include <Arduino.h>



SaberSound::SaberSoundManager::SaberSoundManager(unsigned int dataPin)
	:_dataPin(dataPin)
{
	pinMode(_dataPin, OUTPUT);
}


SaberSound::SaberSoundManager::~SaberSoundManager()
{
}

unsigned long SaberSound::SaberSoundManager::bootSound() const
{
	return _playSound(BOOT_SOUND);
}

unsigned long SaberSound::SaberSoundManager::powerOnSound() const
{
	return _playSound(POWER_ON_SOUND);
}

unsigned long SaberSound::SaberSoundManager::powerOffSound() const
{
	return _playSound(POWER_OFF_SOUND);
}

unsigned long SaberSound::SaberSoundManager::idleSound() const
{
	return _playSound(IDLE_SOUND);
}

unsigned long SaberSound::SaberSoundManager::swingSound() const
{
	return _playSound(SWING_SOUND());
}

unsigned long SaberSound::SaberSoundManager::strikeSound() const
{
	return _playSound(STRIKE_SOUND());
}

unsigned long SaberSound::SaberSoundManager::hitSound() const
{
	return _playSound(HIT_SOUND());
}


unsigned long SaberSound::SaberSoundManager::_playSound(const SaberSound saberSound) const
{
	auto address = saberSound.address;
	if (Serial) {
		Serial.print("Playing sound: ");
		Serial.println(address);
	}

	digitalWrite(_dataPin, LOW);	// We need to ensure that the chip is woken up from sleep mode
	delay(5);

	for (int i = 0; i < 8; i++) {

		if (bitRead(address, i)) { // Read each bit of the sound to be played

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

	return saberSound.duration;
}
