#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

void
create_icewall_room()
{
    set_short("Tunnel at the massive gate");
    set_long("@@long_descr");

    add_exit("east_path6","east","@@east",1,1);
    add_exit("inner_courtyard","west");
    add_exit("north_guard","north","@@north");
    add_exit("south_guard","south","@@south");

    add_cmd_item("gate","open","@@noway");

    add_item(({"gate","massive gate"}),"Massive, ancient gate " +
     "blocks the tunnel to the east. Darkened by age, covered " +
     "by ice, it appears as if it wasn't opened in at least a " +
     "decade. The feeling is reinforced by the fact that the " +
     "gate has been additionaly barricaded.\n");
    add_item("tunnel","The tunnel has been constructed in the " +
     "lower building's east wall, and leads from the Icewall " +
     "Castle's courtyard to the massive gate. The gate is closed " +
     "and barricaded, allowing noone to enter... or leave.\n");  
    add_item(({"guardroom","guardrooms"}),"To the north and south " +
     "small doorways set into the side of the tunnel lead into the " +
     "double gate guardrooms.\n");

    set_tell_time(800);

    add_tell("You hear some footsteps above you, on the second floor " +
     "of the lower building.\n");
    add_tell("You hear water cascading down directly to the west.\n");
}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}                  

string

long_descr()

{ return ("" +
    "This is the gate tunnel, which, in normal conditions, " +
    "allows passage from the inner courtyard to the main gate. " +
    "Someone has barricaded the gate shut, closing the castle " +
    "to the outside world. On both sides of the tunnel you can " +
    "see the doors to the gate guardrooms.\n");
    

}


int
north()
{ 
  write("Squeezing through a half-opened door, you enter " +
   "the north gateroom.\n");
  say(QCTNAME(TP) + " squeezes through a half-opened door.\n");
  return 0;
}

int
south()
{ 
  write("Squeezing through a half-opened door, you enter " +
   "the south gateroom.\n");
  say(QCTNAME(TP) + " squeezes through a half-opened door.\n");
  return 0;
}

int
east()
{
  write("You have yet to learn the skill of passing THROUGH closed " +
   "gates.\n");
  say("Perhaps hoping for a local miracle, " + QTNAME(TP) + " attempts " +
   "to pass through the closed gate, but fails.\n");
  return 1;
}

string
noway()
{
  write("You would need a score of " +
     "minotaurs to accomplish that. The gate is frozen solid " +
     "and sturdily barricaded. All you can do is bang on it.\n");
  say(QCTNAME(TP) + " moves as if to open the gate, but quickly " +
     "abandones the furtive idea.\n");
  return "";
}

int
bang(string str)
{
     if(str != "on gate")
       {
         notify_fail("Bang on what?\n");
         return 0;
       }

     write("You clench your hand in a fist and bang loudly on the " +
       "gate, hoping to be heard inside.\n");
     say(QCTNAME(TP) + " clenches his hand in a fist and bangs " +
       "loudly on the gate.\n");
     tell_room(ROOMSK + "east_path6", "Someone bangs at the " +
       "gate, but the sound is faint and muted. You doubt it carries " +
       "further then this place.\n",TP);
     return 1;
}

void
init()
{
    ::init();

    add_action(bang, "bang");
}        

