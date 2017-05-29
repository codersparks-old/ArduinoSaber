#include "SaberSounds.h"

/*
Function to return a random Swing sound
*/
SaberSound::SaberSound SaberSound::SWING_SOUND() {
	return SWING_SOUNDS[random(8)];
}

/*
Function to return a random HIT_SOUND
*/
SaberSound::SaberSound SaberSound::HIT_SOUND() {
	return HIT_SOUNDS[random(4)];
}

/*
Function to return a random STRIKE_SOUND
*/
SaberSound::SaberSound SaberSound::STRIKE_SOUND() {
	return STRIKE_SOUNDS[random(3)];
}