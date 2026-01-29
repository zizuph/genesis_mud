inherit "/std/object";

#include <macros.h>

#include "../defs.h"

int alarm_h;
int stage=0;

void hotfoot_action();

void create_object()
{
 setuid();
 seteuid(getuid());
 set_name("_trickster_hotfoot_object_");
 set_no_show_composite(1);
}

void hotfoot_action()
{
 int what;

 stage++;

 if(stage==1)
  {
   TP->command("jump");
   write("Your foot is suddenly engulfed in flames!\n");
   say(QTNAME(TP)+"'s foot is suddenly engulfed in flames!\n");
   return;
  }

 if(stage==10)
  {
   write("The flames on your foot has finaly burnt away.\n");
   say("The flames on "+QTNAME(TP)+"'s foot have finally "+
     "gone out.\n");
   remove_alarm(alarm_h);
   remove_object();
  }

 what=random(5);

 switch(what)
  {
   case 0:
     TP->command("jump pain");
     break;
   case 1:
     TP->command("wail");
     break;
   case 2:
     TP->command("wince");
     break;
   case 3:
     write("You start to hop madly around the room, "+
       "fanning your foot in hopes that the flames will go out.\n");
     say(QTNAME(TP)+" hops madly around the room fanning "+
       POS(TP)+" foot, in hopes the flames will go out.\n");
     break; 
   case 4:
     TP->command("sweat");
  }
}

void start()
{
 set_this_player(ENV(TO));
 alarm_h=set_alarm(1.0,4.0,&hotfoot_action());
}

