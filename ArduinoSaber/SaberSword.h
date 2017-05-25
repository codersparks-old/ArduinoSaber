#pragma once
#include "Arduino.h"
#include "SaberStates.h"

namespace Saber {

	class SaberSword
	{
	public:
		SaberSword(byte dataPin);
		~SaberSword();
		void update(SaberState state, long timeInState) const;
	private:
		const byte _dataPin;
	};

}