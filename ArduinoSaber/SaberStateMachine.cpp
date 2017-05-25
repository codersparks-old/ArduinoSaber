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
	case POWERING_ON_STATE:
		_saberSound.reset();
		_powerOn();
		_currentState = IDLE_STATE;
		break;
	case POWERING_OFF_STATE:
		_saberSound.reset();
		_powerOff();
		_currentState = OFF_STATE;
		break;
	case SWING_STATE:
		_saberSound.reset();
		_swing();
		_currentState = IDLE_STATE;
		break;
	case HIT_STATE:
		_saberSound.reset();
		_hit();
		_currentState = IDLE_STATE;
		break;
	case STRIKE_STATE:
		_saberSound.reset();
		_strike();
		_currentState = IDLE_STATE;
		break;
	default:
		/*if (Serial) {
			Serial.print("Don't yet know how to update for state: ");
			Serial.println(_currentState);
		}*/
		break;

	}

	_saberSword.update(_currentState, millis() - _currentStateStartMillis);
	_previousState = _currentState;
}

void Saber::SaberStateMachine::powerChangeEvent()
{
	switch (_currentState) {
	case OFF_STATE:
		_currentState = POWERING_ON_STATE;
		break;
	default:
		_currentState = POWERING_OFF_STATE;
		break;
	}

	_currentStateStartMillis = millis();

}

void Saber::SaberStateMachine::swingEvent()
{

	switch (_currentState) {
	case IDLE_STATE:
		_currentState = SWING_STATE;
		_currentStateStartMillis = millis();
		break;
	default:
		// No - op
		break;
	}
}

void Saber::SaberStateMachine::shockEvent()
{
	switch (_currentState) {
	case IDLE_STATE:
		_currentState = HIT_STATE;
		_currentStateStartMillis = millis();
		break;
	case SWING_STATE:
		_currentState = STRIKE_STATE;
		_currentStateStartMillis = millis();
		break;
	default:
		// no change in state
		break;
	}
}

Saber::SaberState Saber::SaberStateMachine::getCurrentState()
{
	return _currentState;
}

void Saber::SaberStateMachine::playStartupSound()
{
	_saberSound.playSound(SaberSounds::STARTUP);
}

void Saber::SaberStateMachine::_swing() {
	_saberSound.playSwingSound();
}

void Saber::SaberStateMachine::_hit()
{
	_saberSound.playHitSound();
}

void Saber::SaberStateMachine::_strike()
{
	_saberSound.playStrikeSound();
}

void Saber::SaberStateMachine::_idleSound()
{
	if (!_saberSound.isBusy()) {
		// we only trigger a play if the sound board is not busy
		_saberSound.playSound(SaberSounds::IDLE);
	}

}

void Saber::SaberStateMachine::_powerOff()
{
	_saberSound.playSound(SaberSounds::OFF);
}

void Saber::SaberStateMachine::_powerOn()
{
	_saberSound.playSound(SaberSounds::ON);
}
