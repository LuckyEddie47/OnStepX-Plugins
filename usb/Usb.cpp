// USB port switching plugin

#include "Usb.h"
//#include "../../lib/tasks/OnTask.h"
#include "../../lib/gpioEx/GpioEx.h"

//void usbWrapper() { usb.loop(); }

Port myPort[8] = {
      { USB1_NAME, USB1_PIN, USB1_DEFAULT_STATE, USB1_ON_STATE },
      { USB2_NAME, USB2_PIN, USB2_DEFAULT_STATE, USB2_ON_STATE },
      { USB3_NAME, USB3_PIN, USB3_DEFAULT_STATE, USB3_ON_STATE },
      { USB4_NAME, USB4_PIN, USB4_DEFAULT_STATE, USB4_ON_STATE },
      { USB5_NAME, USB5_PIN, USB5_DEFAULT_STATE, USB5_ON_STATE },
      { USB6_NAME, USB6_PIN, USB6_DEFAULT_STATE, USB6_ON_STATE },
      { USB7_NAME, USB7_PIN, USB7_DEFAULT_STATE, USB7_ON_STATE },
      { USB8_NAME, USB8_PIN, USB8_DEFAULT_STATE, USB8_ON_STATE }
    };

void Usb::init() {
  VLF("MSG: Plugins, starting: USB port switcher");

  // start a task that runs every 10 seconds, run at priority level 7
  //tasks.add(10000, 0, true, 7, usbWrapper);

  // get ready for USB port control
  #if defined(USB1_PIN) && (USB1_PIN != OFF)
    pinMode(USB1_PIN, OUTPUT);
  #endif
  #if defined(USB2_PIN) && (USB2_PIN != OFF)
    pinMode(USB2_PIN, OUTPUT);
  #endif
  #if defined(USB3_PIN) && (USB3_PIN != OFF)
    pinMode(USB3_PIN, OUTPUT);
  #endif
  #if defined(USB4_PIN) && (USB4_PIN != OFF)
    pinMode(USB4_PIN, OUTPUT);
  #endif
  #if defined(USB5_PIN) && (USB5_PIN != OFF)
    pinMode(USB5_PIN, OUTPUT);
  #endif
  #if defined(USB6_PIN) && (USB6_PIN != OFF)
    pinMode(USB6_PIN, OUTPUT);
  #endif
  #if defined(USB7_PIN) && (USB7_PIN != OFF)
    pinMode(USB7_PIN, OUTPUT);
  #endif
  #if defined(USB8_PIN) && (USB8_PIN != OFF)
    pinMode(USB8_PIN, OUTPUT);
  #endif
}

// Our loop is deliberately empty as we only need command processing
//void Usb::loop() {}

// Command process is a copy and paste from Features.command.cpp with unwanted stripped out and names changed
bool Usb::command(char *reply, char *command, char *parameter, bool *supressFrame, bool *numericReply, CommandError *commandError) {
  
  // Get USB commands
  if (command[0] == 'G' && command[1] == 'U' && parameter[2] == 0) {
    // :GUXn#
    // return status of USB port (1 for ON, 0 for OFF)
    if (parameter[0] == 'X') { 
      int i = parameter[1] - '1';
      if (i < 0 || i > 7)  { *commandError = CE_PARAM_FORM; return true; }
      char s[255];
        sprintf(s, "%d", myPort[i].value);
        strcat(reply, s);
    } else 
      
    // :GUY0#
    // return active USB ports in the form 00100111 where each digit is enabled/disabled
    if (parameter[0] == 'Y') {
      int i = parameter[1] - '1';
      if (i == -1) {
        for (int j = 0; j < 8; j++) {
          if (myPort[j].pin == OFF) reply[j] = '0'; else reply[j] = '1';
          reply[j + 1] = 0;
        }
        *numericReply = false;
        return true;
      }

      // :GUY[n]#
      // where [n] = 1..8 to get USB port name
      if (i < 0 || i > 7)  { *commandError = CE_PARAM_FORM; return true; }
      if (myPort[i].pin == OFF) { *commandError = CE_0; return true; }
      char s[255];
      strcpy(s, myPort[i].name);
      if (strlen(s) > 10) s[10] = 0;
      strcpy(reply, s);

      *numericReply = false;
    } else return false;
  } else

  // Set USB command
  if (command[0] == 'S' && command[1] == 'U' && parameter[2] == ',') {
    // :SUX[n],V[n]#
    // for example :SUX1,V1#
    if (parameter[0] == 'X') { 
      int i = parameter[1] - '1';
      if (i < 0 || i > 7)  { *commandError = CE_PARAM_FORM; return true; }
      if (myPort[i].pin == OFF) { *commandError = CE_CMD_UNKNOWN; return true; }

      char* conv_end;
      float f = strtof(&parameter[4], &conv_end);
      if (&parameter[4] == conv_end) { *commandError = CE_PARAM_FORM; return true; }
      long v = lroundf(f);

      if (parameter[3] == 'V') {
        if (v >= 0 && v <= 1) { // value 0..1 for enabled or not
          digitalWriteEx(myPort[i].pin, v == myPort[i].active);
        } else *commandError = CE_PARAM_RANGE;
      } else *commandError = CE_PARAM_FORM;
    } else return false;
  } else return false;

  return true;
}

Usb usb;
