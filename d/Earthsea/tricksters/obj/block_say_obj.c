inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

float duration=0.0,timer=0.0;
int alarm_h;

void create_object()
{
 set_name("_trick_block_say_object_");
 add_prop(OBJ_M_NO_DROP,1);
 set_no_show_composite(1);
}

void init()
{
 ::init();
 add_action("block","",1);
}

int is_say(string verb)
{
 string pref;

 if(sscanf(verb,"%ssay",pref)) return 1;
 if(verb=="'") return 1;
 if(verb=="shout") return 1;
 if(verb=="whisper") return 1;
 if(verb=="ask") return 1;
 if(verb=="converse") return 1;
 if(verb=="mumble") return 1;

 return 0;
}

int is_think(string verb)
{
 if(verb=="think") return 1;
 if(verb=="ponder") return 1;

 return 0;
}


int block(string str)
{
 if(is_say(query_verb()))
  {
   write("You open your mouth and try to say something , but your "+
     "vocal cords still hurt from treacherous attack.\n");
   say(QCTNAME(TP)+" tries to say something , but only bubbling "+
     "noice coming out of "+POS(TP)+" mouth.\n");
   return 1;
  }

 if(is_think(query_verb()))
  {
   write("The sensation in your neck is that painfull you even "+
     "unable to think!\n");
   return 1;
  }

 return 0;
}

void remove_me()
{
 write("Your vocal cords seem to get back to normal. You think you "+
   "are able to talk again.\n");
 remove_object();
}

void add_duration(float secs) {duration=duration+secs;}

void advance_timer()
{
 timer=timer+1.0;
 if(timer>=duration)
  {
   remove_alarm(alarm_h);
   remove_me();
  }
}

void start_timer()
 {
  set_this_player(ENV(TO));
  write("The blow hurts your vocal cords. You don't think you are "+
    "able to talk now.\n");
  alarm_h=set_alarm(1.0,1.0,&advance_timer());
 }

