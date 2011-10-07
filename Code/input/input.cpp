#include <WinCore/windows/windows.h>
#include <Xinput.h>
#include "input.h"

#pragma comment(lib, "xinput.lib")

namespace aurora {
namespace input {

Input::Input() {
  
}

Input::~Input() {

}

void Input::Poll() {
  controller1.Handle(null);
  /*DWORD dwResult;    
  for (DWORD i=0; i < 1; i++ ) {
    XINPUT_STATE state;
    ZeroMemory( &state, sizeof(XINPUT_STATE) );
    // Simply get the state of the controller from XInput.
    dwResult = XInputGetState( i, &state );
    if( dwResult == ERROR_SUCCESS ) { 
      // Controller is connected 
      if (controller1.enabled == false) {
        //trigger event
      }
      
    } else {
      // Controller is not connected 
      controller1.enabled = false;
    }
  }*/
}

}
}