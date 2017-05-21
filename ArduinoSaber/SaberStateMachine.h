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
		HIT_STATE = 4
	};

	class SaberStateMachine
	{
	public:
		SaberStateMachine(byte soundDataPin, byte soundBusyPin, byte soundResetPin, byte swordDataPin);
		SaberStateMachine(byte soundDataPin, byte soundBusyPin, byte soundResetPin, byte swordDataPin, SaberState initialState);
		~SaberStateMachine();
		void update();
		SaberState getCurrentState();

	private:
		const SaberSound _saberSound;
		const SaberSword _saberSword;

		SaberState _currentState;
		SaberState _previousState;

		void _idleSound();

	};

} // End namespace Saber
