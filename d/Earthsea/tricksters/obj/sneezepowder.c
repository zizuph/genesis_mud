inherit "/std/object";

#include <macros.h>

#include "../defs.h"

int alarm_h;
int count=0;
int length=0;

void sneeze_action();

void end_in(int t)
{
 count+=length-t;
}

void set_length(int l)
{
 count=0;
 length=l;
}

void create_object()
{
 setuid();
 seteuid(getuid());
 set_name("_trickster_sneeze_object_");
 set_no_show_composite(1);
}

void sneeze_action()
{
 int what;

 count++;
 if(count==1)
  {
   write("You feel a funny twitch in your nose!!\n");
   return;
  }

 if(count==length)
  {
   write("Your sinuses finally clear up and you cease to sneeze.\n");
   remove_alarm(alarm_h);
   remove_object();
   return;
  }

 what=random(6);
 switch(what)
  {
   case 0:
     write("You sniff pitifully.\n");
     say(C(QTNAME(TP))+" sniffs pitifully.\n");
     break;
   case 1:
     write("You sneeze loudly.\n");
     say(C(QTNAME(TP))+" sneezes loudly.\n");
     break;
   case 2:
     write("You sneeze violently.\n");
     say(C(QTNAME(TP))+" sneezes violently.\n");
     break;
   case 3:
     write("You sneeze uncontrollably.\n");
     say(C(QTNAME(TP))+" sneezes uncontrollably.\n");
     break;
   case 4:
     write("You sneeze softly.\n");
     say(C(QTNAME(TP))+" sneezes softly.\n");
     break;
   case 5:
     write("Your nose starts to run somewhat.\n");
     say(C(QTNAME(TP))+"'s nose starts to run somewhat.\n");
     break;
  } 
}

void start()
{
 set_this_player(ENV(TO));
 alarm_h=set_alarm(5.0,10.0,&sneeze_action());
}

