// USB port switching plugin
#pragma once

#include "../../Common.h"
#include "../../lib/commands/CommandErrors.h"

class Usb {
public:
  // the initialization method must be present and named: void init();
  void init();

  bool command(char *reply, char *command, char *parameter, bool *supressFrame, bool *numericReply, CommandError *commandError);

  //void loop();

private:
  // Plugin config
  #define USB1_PIN                   OFF //    OFF, n. I/O pin controlling the port state.    Option
  #define USB1_NAME               "USB1" //    "USB..", Name of the device being controlled.  Option
  #define USB1_ON_STATE             HIGH //    HIGH, LOW Port control pin ON (active) state.  Option
  #define USB2_PIN                   OFF //    OFF, n. I/O pin controlling the port state.    Option
  #define USB2_NAME               "USB2" //    "USB..", Name of the device being controlled.  Option
  #define USB2_ON_STATE             HIGH //    HIGH, LOW Port control pin ON (active) state.  Option
  #define USB3_PIN                   OFF //    OFF, n. I/O pin controlling the port state.    Option
  #define USB3_NAME               "USB3" //    "USB..", Name of the device being controlled.  Option
  #define USB3_ON_STATE             HIGH //    HIGH, LOW Port control pin ON (active) state.  Option
  #define USB4_PIN                   OFF //    OFF, n. I/O pin controlling the port state.    Option
  #define USB4_NAME               "USB4" //    "USB..", Name of the device being controlled.  Option
  #define USB4_ON_STATE             HIGH //    HIGH, LOW Port control pin ON (active) state.  Option
  #define USB5_PIN                   OFF //    OFF, n. I/O pin controlling the port state.    Option
  #define USB5_NAME               "USB5" //    "USB..", Name of the device being controlled.  Option
  #define USB5_ON_STATE             HIGH //    HIGH, LOW Port control pin ON (active) state.  Option
  #define USB6_PIN                   OFF //    OFF, n. I/O pin controlling the port state.    Option
  #define USB6_NAME               "USB6" //    "USB..", Name of the device being controlled.  Option
  #define USB6_ON_STATE             HIGH //    HIGH, LOW Port control pin ON (active) state.  Option
  #define USB7_PIN                   OFF //    OFF, n. I/O pin controlling the port state.    Option
  #define USB7_NAME               "USB7" //    "USB..", Name of the device being controlled.  Option
  #define USB7_ON_STATE             HIGH //    HIGH, LOW Port control pin ON (active) state.  Option
  #define USB8_PIN                   OFF //    OFF, n. I/O pin controlling the port state.    Option
  #define USB8_NAME               "USB8" //    "USB..", Name of the device being controlled.  Option
  #define USB8_ON_STATE             HIGH //    HIGH, LOW Port control pin ON (active) state.  Option
};

typedef struct Port {
   const char* name;
   int16_t pin;
   const int16_t active;
} Port;

Port port[8] = {
      { USB1_NAME, USB1_PIN, USB1_ON_STATE },
      { USB2_NAME, USB2_PIN, USB2_ON_STATE },
      { USB3_NAME, USB3_PIN, USB3_ON_STATE },
      { USB4_NAME, USB4_PIN, USB4_ON_STATE },
      { USB5_NAME, USB5_PIN, USB5_ON_STATE },
      { USB6_NAME, USB6_PIN, USB6_ON_STATE },
      { USB7_NAME, USB7_PIN, USB7_ON_STATE },
      { USB8_NAME, USB8_PIN, USB8_ON_STATE }
    };

extern Usb usb;
