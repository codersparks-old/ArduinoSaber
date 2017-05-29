#pragma once
#include "SaberSounds.h"

namespace SaberSound {
class SaberSoundManager
{
public:
	SaberSoundManager(unsigned int dataPin);
	~SaberSoundManager();
	unsigned long bootSound() const;
	unsigned long powerOnSound() const;
	unsigned long powerOffSound() const;
	unsigned long idleSound() const;
	unsigned long swingSound() const;
	unsigned long strikeSound() const;
	unsigned long hitSound() const;

protected:
	unsigned long _playSound(const SaberSound saberSound) const;
	unsigned int _dataPin;
};

} // End of namespace 