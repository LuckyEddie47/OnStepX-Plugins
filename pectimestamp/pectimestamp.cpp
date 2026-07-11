

#include "pectimestamp.h"
#include "../../lib/tasks/OnTask.h"
#include "../../lib/sense/Sense.h"
#include "../../lib/convert/Convert.h"
#include "../../telescope/mount/site/Site.h"

#if (PEC_SENSE) != OFF

static void pecTsTask(){ pecTimestamp.poll(); }

void PecTimestamp::init(){
  senseHandle=sense.add(PEC_SENSE_PIN,PEC_SENSE_INIT,PEC_SENSE);
  taskHandle=tasks.add(1,0,true,5,pecTsTask,"PecTS");
}
void PecTimestamp::poll(){
  if(senseHandle && sense.changed(senseHandle)){
    lastTriggerTime=site.getDateTime().hour;
    haveTrigger=true;
  }
}
bool PecTimestamp::command(char *reply,char *command,char *parameter,bool *suppressFrame,bool *numericReply,CommandError *commandError){
  (void)suppressFrame;(void)commandError;
  if(command[0]=='V'&&command[1]=='X'&&parameter[0]==0){
    if(!haveTrigger) strcpy(reply,"0");
    else dtostrf(lastTriggerTime,0,7,reply);
    *numericReply=false;
    return true;
  }
  return false;
}

PecTimestamp pecTimestamp;
#endif
