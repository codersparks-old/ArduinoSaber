#include "SaberStateMachine.h"



Saber::SaberStateMachine::SaberStateMachine(byte soundDataPin, byte soundBusyPin, byte soundResetPin, byte swordDataPin)
	: _saberSound(soundDataPin, soundBusyPin, soundResetPin), _saberSword(swordDataPin), _currentState(SaberState::OFF_STATE)
{
}

Saber::SaberStateMachine::SaberStateMachine(byte soundDataPin, byte soundBusyPin, byte soundResetPin, byte swordDataPin, SaberState initialState)
	: _saberSound(soundDataPin, soundBusyPin, soundResetPin), _saberSword(swordDataPin), _currentState(initialState)
{
}

Saber::SaberStateMachine::~SaberStateMachine()
{
}

void Saber::SaberStateMachine::update()
{
	switch (_currentState) {
	case IDLE_STATE:
		_idleSound();
		break;
	default:
		if (Serial) {
			Serial.print("Don't yet know how to update for state: ");
			Serial.println(_currentState);
		}

	}

	_previousState = _currentState;
}

Saber::SaberState Saber::SaberStateMachine::getCurrentState()
{
	return _currentState;
}

void Saber::SaberStateMachine::_idleSound()
{
	if (!_saberSound.isBusy()) {
		// we only trigger a play if the sound board is not busy
		_saberSound.playSound(SaberSounds::IDLE);
	}

}
