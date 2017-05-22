#pragma once
#include "SaberSound.h"
#include "SaberSword.h"
#include "Arduino.h"

namespace Saber {

	enum SaberState { 
		OFF_STATE = 0,
		IDLE_STATE = 1,
		SWING_STATE = 2,
		STRIKE_STATE = 3,
		HIT_STATE = 4,
		POWERING_ON_STATE = 5,
		POWERING_OFF_STATE = 6
	};

	class SaberStateMachine
	{
	public:
		SaberStateMachine(byte soundDataPin, byte soundBusyPin, byte soundResetPin, byte swordDataPin);
		SaberStateMachine(byte soundDataPin, byte soundBusyPin, byte soundResetPin, byte swordDataPin, SaberState initialState);
		~SaberStateMachine();
		void update();
		void powerChangeEvent();
		void swingEvent();
		void shockEvent();
		SaberState getCurrentState();
		void playStartupSound();
		

	private:
		const SaberSound _saberSound;
		const SaberSword _saberSword;

		SaberState _currentState;
		SaberState _previousState;

		void _idleSound();
		void _powerOff();
		void _powerOn();
		void _swing();
		void _hit();
		void _strike();
	};

} // End namespace Saber
