/*
 Name:		ArduinoSaber.ino
 Created:	5/20/2017 7:45:45 PM
 Author:	codersparks
*/

#include "SaberStateMachine.h"

const byte SOUND_BUSY_PIN = 13;
const byte SOUND_DATA_PIN = 12;
const byte SOUND_RESET_PIN = 11;
const byte SWORD_DATA_PIN = 10;


volatile Saber::SaberStateMachine stateMachine(SOUND_DATA_PIN, SOUND_BUSY_PIN, SOUND_RESET_PIN, SWORD_DATA_PIN, Saber::SaberState::IDLE_STATE);

unsigned long lastRun = 0;

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(115200);

	while (!Serial); // Wait for serial to be up and running


}

// the loop function runs over and over again until power down or reset
void loop() {
		if (Serial) {
			Serial.print("Current Saber State: ");
			Serial.println(stateMachine.getCurrentState());
		}
		stateMachine.update();
}
