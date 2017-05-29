#pragma once

namespace SaberStates {

	/*
	Enum used to represent the states within the SaberState Machine

	Post states are use to fill for while a sound plays
	*/
	enum SaberState {
		BOOTUP_STATE,
		OFF_STATE,
		POWERING_OFF_STATE,
		POWERING_ON_STATE,
		WAIT_STATE, // Used to wait for sound to play (an idea to remove the "post" states
		IDLE_STATE,
		POST_IDLE_STATE,
		SWING_STATE,
		POST_SWING_STATE,
		SHOCK_STATE,
		POST_SHOCK_STATE
	};

}
