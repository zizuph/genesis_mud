inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

int alarm_h;
int count=0;

void laugh_action();

void create_object()
{
 setuid();
 seteuid(getuid());
 set_name("_trickster_laugh_object_");
 set_no_show_composite(1);
 add_prop(OBJ_I_NO_DROP,"");
}

void laugh_action()
{
 int what;
 string emote;

 count++;
 if(count==15)
  {
   write("The uncontrollable urge to laugh has finally ceased.\n");
   remove_alarm(alarm_h);
   remove_object();
   return;
  }

 what=random(6);
 switch(what)
  {
   case 0: emote="giggle"; break;
   case 1: emote="chuckle"; break;
   case 2: emote="laugh"; break;
   case 3: emote="laugh hyst"; break;
   case 4: emote="laugh loud"; break;
   case 5: emote="laugh uncont"; break;
  } 

 TP->command(emote);
}

void start()
{
 set_this_player(ENV(TO));
 write("You feel the uncontrollable urge to laugh.\n");
 alarm_h=set_alarm(5.0,10.0,&laugh_action());
}

