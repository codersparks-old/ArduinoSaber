#include "SaberStateManager.h"
#include "Arduino.h"



SaberStates::SaberStateManager::SaberStateManager(SaberSoundManager *soundManager, SaberBladeManager *bladeManager)
	:
	_soundManager(soundManager),
	_bladeManager(bladeManager),
	_currentState(SaberStates::OFF_STATE),
	_previousState(SaberStates::OFF_STATE),
	_nextState(SaberStates::OFF_STATE),
	_stateDuration(100),
	_stateStartMillis(0)
{
}

SaberStates::SaberStateManager::~SaberStateManager()
{
}

void SaberStates::SaberStateManager::handlePowerOn()
{
	_changeState(SaberStates::POWERING_ON_STATE);
}

void SaberStates::SaberStateManager::handlePowerOff()
{
	_changeState(SaberStates::POWERING_OFF_STATE);
}

void SaberStates::SaberStateManager::handleSwing()
{
	_changeState(SaberStates::SWING_STATE);
}

void SaberStates::SaberStateManager::handleShock()
{
	_changeState(SaberStates::SHOCK_STATE);
}

void SaberStates::SaberStateManager::_changeState(SaberState newState)
{
	_previousState = _currentState;
	_currentState = newState;
	_stateStartMillis = millis();
}

void SaberStates::SaberStateManager::update()
{

	switch (_currentState) {
	case SaberStates::POWERING_ON_STATE:
		_stateDuration = _soundManager->powerOnSound();
		_nextState = IDLE_STATE;
		_changeState(WAIT_STATE);
		break;
	case SaberStates::POWERING_OFF_STATE:
		_stateDuration = _soundManager->powerOffSound();
		_nextState = SaberState::OFF_STATE;
		_changeState(SaberStates::WAIT_STATE);
		break;
	case SaberStates::IDLE_STATE:
		_stateDuration = _soundManager->idleSound();
		_nextState = SaberState::IDLE_STATE; // Idle just loops
		_changeState(SaberStates::WAIT_STATE);
		break;
	case SaberStates::SWING_STATE:
		_stateDuration = _soundManager->swingSound();
		_nextState = SaberState::IDLE_STATE;
		_changeState(SaberStates::POST_SWING_STATE);
		break;
	case SaberStates::SHOCK_STATE:
		// We play strike sound if it was swinging or hit otherwise
		switch (_previousState)
		{
		case SWING_STATE:
		case POST_SWING_STATE:
			_stateDuration = _soundManager->strikeSound();
			break;
		default:
			_stateDuration = _soundManager->hitSound();
			break;
		}
		_nextState = SaberState::IDLE_STATE;
		_changeState(SaberStates::POST_SHOCK_STATE);
		break;
	case SaberStates::POST_SWING_STATE:
	case SaberStates::POST_SHOCK_STATE:
	case SaberStates::WAIT_STATE:
		if (millis() - _stateStartMillis >= _stateDuration) {
			_changeState(_nextState);
		}
		break;
	default:
		// No op
		break;


	}
}

bool SaberStates::SaberStateManager::isPoweredOn() const
{
	if (_currentState == SaberStates::OFF_STATE || _currentState == SaberStates::POWERING_OFF_STATE) {
		return false;
	}
	else {
		return true;
	}
}
