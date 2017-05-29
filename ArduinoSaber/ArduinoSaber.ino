/*
 Name:		ArduinoSaber.ino
 Created:	5/25/2017 6:56:51 PM
 Author:	codersparks
*/
#include "Arduino.h"
#include "SaberStateManager.h"
#include "SaberSoundManager.h"
#include "SaberBladeManager.h"
#include "EnableInterrupt-0.9.7\EnableInterrupt.h"

using SaberSound::SaberSoundManager;
using SaberBlade::SaberBladeManager;
using SaberStates::SaberStateManager;

const byte SOUND_DATA_PIN = 12;
const byte POWER_BUTTON_PIN = 7;
const byte SWING_BUTTON_PIN = 6;
const byte SHOCK_BUTTON_PIN = 5;

SaberSoundManager soundManager(SOUND_DATA_PIN);
SaberSoundManager *soundManagerPointer = &soundManager;
SaberBladeManager bladeManager;
SaberBladeManager *bladeManagerPointer = &bladeManager;
SaberStateManager stateManager(soundManagerPointer, bladeManagerPointer);

long lastEventTime = 0;
const int debounceTime = 500;

bool checkForDebounce()
{
	return millis() - lastEventTime > debounceTime;
}

void handleSwingEvent()
{
	if (checkForDebounce()) {
		stateManager.handleSwing();
		lastEventTime = millis();
	}

}

void handleShockEvent()
{
	stateManager.handleShock();
	lastEventTime = millis();
	
}

// There are certain interrupts that we only want to handle when we are powered on so we enable them in a function
void registerPoweredOnInterrupts()
{
	enableInterrupt(SWING_BUTTON_PIN, handleSwingEvent, FALLING);
	enableInterrupt(SHOCK_BUTTON_PIN, handleShockEvent, FALLING);
}

// Same as register we need to deregister interrupts
void deregisterPoweredOnInterrupts()
{
	disableInterrupt(SWING_BUTTON_PIN);
	disableInterrupt(SHOCK_BUTTON_PIN);
}

void handlePowerEvent() {
	if (checkForDebounce()) {
		lastEventTime = millis();
		if (stateManager.isPoweredOn()) {
			stateManager.handlePowerOff();
			deregisterPoweredOnInterrupts();
		}
		else {
			stateManager.handlePowerOn();
			registerPoweredOnInterrupts();
		}
	}
}

// the setup function runs once when you press reset or power the board
void setup() {
	// if analog input pin 0 is unconnected, random analog
	// noise will cause the call to randomSeed() to generate
	// different seed numbers each time the sketch runs.
	// randomSeed() will then shuffle the random function.
	randomSeed(analogRead(0));

	auto duration = soundManager.bootSound();
	delay(duration);

	pinMode(POWER_BUTTON_PIN, INPUT_PULLUP);
	pinMode(SHOCK_BUTTON_PIN, INPUT_PULLUP);
	pinMode(SWING_BUTTON_PIN, INPUT_PULLUP);
	enableInterrupt(POWER_BUTTON_PIN, handlePowerEvent, FALLING);

}

// the loop function runs over and over again until power down or reset
void loop() {
	stateManager.update();
}
