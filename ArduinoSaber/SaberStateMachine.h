#pragma once
#include "SaberSound.h"
#include "SaberSword.h"
#include "SaberStates.h"
#include "Arduino.h"

namespace Saber {

	

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

		long _currentStateStartMillis;

		void _idleSound();
		void _powerOff();
		void _powerOn();
		void _swing();
		void _hit();
		void _strike();
	};

} // End namespace Saber
