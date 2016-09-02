// ----------------------------------------------------------------------------
// Callbacks.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "ArduinoJson.h"
#include "ModularServer.h"
#include "Constants.h"
#include "Controller.h"
#include "Globals.h"


namespace callbacks
{
void enableCallback();

void disableCallback();

void stopCallback();

void getControllerInfoCallback();

void moveCallback();

void playToneCallback();

// Set Field Callbacks
void setWaypointCountCallback();

void setWaypointTravelDurationCallback();

// EventController Callbacks
void waypointRepeatCallback(int index);

// ISR Callbacks
void motorDriveCallback();

void motionCallback();

void soundCallback();
}
#endif
