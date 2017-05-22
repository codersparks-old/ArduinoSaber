/*
 Name:		ArduinoSaber.ino
 Created:	5/20/2017 7:45:45 PM
 Author:	codersparks
*/

#include "SaberStateMachine.h"
#include "EnableInterrupt.h"

const byte SOUND_BUSY_PIN = 13;
const byte SOUND_DATA_PIN = 12;
const byte SOUND_RESET_PIN = 11;
const byte SWORD_DATA_PIN = 10;

const byte POWER_INTERRUPT_PIN = 9;
const byte SWING_INTERRUPT_PIN = 8;
const byte HIT_INTERRUPT_PIN = A1;

const int DEBOUNCE_DELAY = 200;


Saber::SaberStateMachine stateMachine(SOUND_DATA_PIN, SOUND_BUSY_PIN, SOUND_RESET_PIN, SWORD_DATA_PIN);

long lastPowerInterrupt = 0;

void registerPowerInterrupts() {
	enableInterrupt(POWER_INTERRUPT_PIN, powerInterrupt, FALLING);
}

void registerOtherInterrupts() {
	enableInterrupt(SWING_INTERRUPT_PIN, swingInterrupt, FALLING);
	enableInterrupt(HIT_INTERRUPT_PIN, hitInterrupt, FALLING);
}

void disableOtherInterrupts() {
	disableInterrupt(SWING_INTERRUPT_PIN);
	disableInterrupt(HIT_INTERRUPT_PIN);
}

// Function is called on power change event
void powerInterrupt() {

	if (millis() > lastPowerInterrupt + DEBOUNCE_DELAY) {
		stateMachine.powerChangeEvent();

		// We only want the other interrupts enabled if the saber is either powering off or is powered off.
		if (stateMachine.getCurrentState() == Saber::SaberState::OFF_STATE || stateMachine.getCurrentState() == Saber::SaberState::POWERING_OFF_STATE) {
			disableOtherInterrupts();
		}
		else {
			registerOtherInterrupts();
		}

		lastPowerInterrupt = millis();
	}

}

void swingInterrupt() {
	if (millis() > lastPowerInterrupt + DEBOUNCE_DELAY) {
		stateMachine.swingEvent();

		lastPowerInterrupt = millis();
	}

}

void hitInterrupt() {
	if (millis() > lastPowerInterrupt + DEBOUNCE_DELAY) {
		stateMachine.shockEvent();

		lastPowerInterrupt = millis();
	}

}


// the setup function runs once when you press reset or power the board
void setup() {

	// We use an unused analog pin to seed the randmon number generator
	randomSeed(analogRead(A0));

	Serial.begin(115200);

	while (!Serial); // Wait for serial to be up and running

	pinMode(POWER_INTERRUPT_PIN, INPUT_PULLUP);
	pinMode(SWING_INTERRUPT_PIN, INPUT_PULLUP);
	pinMode(HIT_INTERRUPT_PIN, INPUT_PULLUP);

	stateMachine.playStartupSound();

	registerPowerInterrupts();
	registerOtherInterrupts();

}

// the loop function runs over and over again until power down or reset
void loop() {
		/*if (Serial) {
			Serial.print("Current Saber State: ");
			Serial.println(stateMachine.getCurrentState());
		}*/
		stateMachine.update();
}
