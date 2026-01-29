inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

int alarm_h;
int count=0;
int length=0;

void end_in(int t)
{
 count+=length-t;
}

void set_length(int l)
{
 length=l;
 count=0;
}

void itch_action();

void create_object()
{
 setuid();
 seteuid(getuid());
 set_name("_trickster_itch_object_");
 set_no_show_composite(1);
 add_prop(OBJ_I_NO_DROP,"");
}

void itch_action()
{
 int what;
 string emote;

 count++;
 if(count==1)
  {
   write("You feel itchy all over!!!\n");
   return;
  }

 if(count==length)
  {
   write("The annoying itch has finally gone away.\n");
   remove_alarm(alarm_h);
   remove_object();
   return;
  }

 what=random(7);
 switch(what)
  {
   case 0: emote="grumble"; break;
   case 1: emote="scratch"; break;
   case 2: emote="scratch chin"; break;
   case 3: emote="scratch back"; break;
   case 4: emote="scratch behind"; break;
   case 5: emote="scratch ear"; break;
   case 6: emote="scratch nose";
  } 

 TP->command(emote);
}

void start()
{
 set_this_player(ENV(TO));
 alarm_h=set_alarm(5.0,10.0,&itch_action());
}

