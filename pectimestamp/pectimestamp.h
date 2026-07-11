// PEC timestamp retrieval plugin
// Monitors PEC index sense signal and stores last time detected
// :VX# returns last PEC index time
// PLUGIN[n]_COMMAND_PROCESSING must be set ON in Plugins.config.h

#pragma once
#include "../../Common.h"
#include "../../lib/commands/CommandErrors.h"

#if (PEC_SENSE) != OFF

class PecTimestamp {
public:
  void init();
  void poll();
  bool command(char *reply,char *command,char *parameter,bool *suppressFrame,bool *numericReply,CommandError *commandError);
private:
  uint8_t senseHandle=0;
  uint8_t taskHandle=0;
  bool haveTrigger=false;
  double lastTriggerTime=0.0;
};
extern PecTimestamp pecTimestamp;

#endif
