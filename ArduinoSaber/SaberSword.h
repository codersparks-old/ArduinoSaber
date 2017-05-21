#pragma once
#include "Arduino.h"

namespace Saber {

	class SaberSword
	{
	public:
		SaberSword(byte dataPin);
		~SaberSword();
	private:
		const byte _dataPin;
	};

}