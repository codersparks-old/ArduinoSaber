#pragma once

#include "SaberState.h"
#include "SaberSoundManager.h"
#include "SaberBladeManager.h"

using SaberSound::SaberSoundManager;
using SaberBlade::SaberBladeManager;

namespace SaberStates {

	class SaberStateManager
	{
	public:
		SaberStateManager(SaberSoundManager *soundManager, SaberBladeManager *bladeManager);
		~SaberStateManager();
		void handlePowerOn();
		void handlePowerOff();
		void handleSwing();
		void handleShock();
		void update();
		bool isPoweredOn() const;
	
	private:
		void _changeState(SaberState newState);
		SaberSoundManager *_soundManager;
		SaberBladeManager *_bladeManager;
		SaberState _currentState;
		SaberState _previousState;
		SaberState _nextState;
		long _stateDuration;
		long _stateStartMillis;

	};
} // End of SaberStateMAnager namespace

