/*
n27.c is N
n30.c is SW
*/
// The room contains glass vial, part of magic square quest.
inherit "/std/room";

#include <tasks.h>
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/magic_square.h"

create_room()
{
  set_short("Rocky tunnel");
  set_long("This rocky tunnel continues to the north and"
+" southwest.  The ground is rough and uneven, and stalagmites thrust"
+" upward at irregular intervals.\n");

  AE(L4+"n27","north",0,DIRT);
  AE(L4+"n30","southwest",0,DIRT);

  add_prop(ROOM_I_LIGHT,0);
  IN;

  add_item ("stalagmite",
    "It is unusually thick and seems to be able to support a climber.\n");
  
  AI("stalagmites", 
     "The stalagmites poke up from the ground here.  They are " +
     "conical mineral formations deposited by dripping " +
     "water. One of them draws your attention.\n");
  
  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
	 "passageway"}), "Very uninteresting stone.\n"); 

  AI(({"dirt","stone","stones","rock","rocks","rubble","debris"}),
     "It clutters the floor, making passage difficult.\n");
  
}


void
init()
{
  ::init();
  add_action ("do_climb", "climb");
}

int
do_climb (string str)
{
  object tp = this_player();
  
  notify_fail ("Climb what?\n");
  if (!str || str != "stalagmite")
    return 0;

  if (tp->query_fatigue() < tp->query_max_fatigue()/7)
    {
      tp->catch_msg ("You are too tired to climb the stalagmite.\n");
      return 1;
    }
  
  if (tp->resolve_task (TASK_DIFFICULT, ({ SS_CLIMB, TS_DEX})) > 0)
    {
      tp->catch_msg ("You climb up the stalagmite.\n");
      say (QCTNAME(tp) + " climbs the stalagmite.\n");
      tp->move_living ("M", L4 + "stalagmite",1);
      tp->add_fatigue (- tp->query_max_fatigue()/7);
      say (QCTNAME(tp) + " climbs up the stalagmite.\n");
      return 1;
    }
  
  // failure
  tp->catch_msg (
       "You start climbing the stalagmite but slip and fall down.\n");
  say (QCTNAME(tp) +
       " starts to climb the stalagmite but slips and falls down.\n");
  tp->add_fatigue (- tp->query_max_fatigue()/7);
  return 1;
}



