#include <math.h>
#include <WinCore/windows/windows.h>
#include <Xinput.h>
#include "controller.h"
#include "xbox360_controller.h"

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30


#pragma comment(lib, "xinput.lib")

namespace aurora {
namespace input {

Xbox360Controller::Xbox360Controller() {
  index_ = 0;
  memset(&state,0,sizeof(state));
  memset(&last_state,0,sizeof(last_state));
}

Xbox360Controller::~Xbox360Controller() {

}


bool Xbox360Controller::A() {
  return (bool)(XINPUT_GAMEPAD_A & state.buttons);
}

bool Xbox360Controller::B() {
  return (bool)(XINPUT_GAMEPAD_B & state.buttons);
}

bool Xbox360Controller::X() {
  return (bool)(XINPUT_GAMEPAD_X & state.buttons);
}

bool Xbox360Controller::Y() {
  return (bool)(XINPUT_GAMEPAD_Y & state.buttons);
}

bool Xbox360Controller::Up() {
  return (bool)(XINPUT_GAMEPAD_DPAD_UP & state.buttons);
}

bool Xbox360Controller::Down() {
  return (bool)(XINPUT_GAMEPAD_DPAD_DOWN & state.buttons);
}

bool Xbox360Controller::Left() {
  return (bool)(XINPUT_GAMEPAD_DPAD_LEFT & state.buttons);
}

bool Xbox360Controller::Right() {
  return (bool)(XINPUT_GAMEPAD_DPAD_RIGHT & state.buttons);
}

bool Xbox360Controller::Start() {
  return (bool)(XINPUT_GAMEPAD_START & state.buttons);
}

bool Xbox360Controller::Select() {
  return (bool)(XINPUT_GAMEPAD_BACK & state.buttons);
}

float Xbox360Controller::LeftTrigger() {
  return (float)state.left_trigger * (1.0f/255.0f);
}
float Xbox360Controller:: RightTrigger() {
  return (float)state.right_trigger * (1.0f/255.0f);
}

float Xbox360Controller::LeftThumbDirection() {
   return CalculateDirection(state.thumb_lx,state.thumb_ly);
}

float Xbox360Controller::LeftThumbMagnitude() {
  return CalculateMagnitude(state.thumb_lx,state.thumb_ly);
}

float Xbox360Controller::RightThumbDirection() {
  return CalculateDirection(state.thumb_rx,state.thumb_ry);
}

float Xbox360Controller::RightThumbMagnitude() {
  return CalculateMagnitude(state.thumb_rx,state.thumb_ry);
}

void Xbox360Controller::Handle(void* data) {
  XINPUT_STATE xstate;
  ZeroMemory( &xstate, sizeof(XINPUT_STATE) );
  DWORD result = XInputGetState( index_, &xstate );
  if( result == ERROR_SUCCESS ) { 
    // Controller is connected 
    if (enabled_ == false) {
      //trigger event
    }
    memcpy(&last_state,&state,sizeof(state));
    enabled_ = true;
    state.buttons = xstate.Gamepad.wButtons;
    state.left_trigger = xstate.Gamepad.bLeftTrigger;
    state.right_trigger = xstate.Gamepad.bRightTrigger;
    state.thumb_lx = xstate.Gamepad.sThumbLX;
    state.thumb_ly = xstate.Gamepad.sThumbLY;
    state.thumb_rx = xstate.Gamepad.sThumbRX;
    state.thumb_ry = xstate.Gamepad.sThumbRY;
  } else {
    enabled_ = false;
  }
}

float Xbox360Controller::CalculateMagnitude(sint16_t x,sint16_t y) {
    //determine how far the controller is pushed
  float magnitude = sqrt((float)x*(float)x + (float)y*(float)y);

  float normalizedMagnitude = 0;

  //check if the controller is outside a circular dead zone
  if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
    //clip the magnitude at its expected maximum value
    if (magnitude > 32767) magnitude = 32767;
  
    //adjust magnitude relative to the end of the dead zone
    magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

    //optionally normalize the magnitude with respect to its expected range
    //giving a magnitude value of 0.0 to 1.0
    normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
  } else { //if the controller is in the deadzone zero out the magnitude
  	magnitude = 0.0;
	  normalizedMagnitude = 0.0;
  }

  return normalizedMagnitude;
}

float Xbox360Controller::CalculateDirection(sint16_t x,sint16_t y) {
  float magnitude = sqrt((float)x*(float)x + (float)y*(float)y);
  //determine the direction the controller is pushed
  float normalizedLX = (float)x / magnitude;
  float normalizedLY = (float)y / magnitude;
  return atan2(normalizedLY,normalizedLX);
}

}
}