/*
 * Village road
 * TAPAKAH 04/2005
 */

inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"
#include "../../nspeir.h"
#include "../../village/village.h"

object c_private;
object sergeant;
int has_garbage;

int collect_garbage(string str);

void
create_gvillage_road()
{
  ::create_khalakhor_room();

  set_short("A path inside " + VILLAGENAME);
  set_long("You are walking on the path in the goblin village of " + VILLAGENAME + " "+
	   "You hear snow and ice crust croaking under your feet. It is quite "+
	   "cold and the wind is blowing strongly. The village has been established "+
	   "on a clearing between the Currain ocean and the dark forest, although "+
	   "it is biting more and more into the trees as it expands. ");
  add_item(({"huts"}),
	   "Crudely built but sturdily looking huts look to be serving home for the\n"+
	   "village inhabitants.\n");
  add_prop(ROOM_I_INSIDE,0);

  reset_room();
}

void
init()
{

  ::init();
  add_action(collect_garbage,"collect");
  add_action(collect_garbage,"clean");
  add_action(collect_garbage,"gather");
}

void
reset_room()
{

  has_garbage = 1;
  add_item(({"dirt","refuse","garbage"}),
	   "Piles of dirt lay everywhere along the path. You wonder how much time and\n"+
	   "effort will take to gather all of it and make this place look cleaner.\n");
}
int
collect_garbage(string str)
{
  object garbage;
  
  if(!str)
    notify_fail("Collect what?\n");

  if(str == "garbage") {
    if(has_garbage) {
      write("You manage to collect quite a pile of garbage cleaning this space.\n");
      say(QCTNAME(TP) + " manages to collect a pile of garbage cleaning this space.\n");
      garbage = clone_object(GARBAGE);
      garbage->move(TO);
      has_garbage = 0;
      remove_item("dirt");
      remove_item("refuse");
      remove_item("garbage");
    }
    else
      write("But the room looks clean already!\n");
    return 1;
  }
  notify_fail("Collect what?\n");
  return 0;
}

string
query_garbage_desc()
{
  if(has_garbage)
    return "Typically for a goblin settlement, dirt and refuse lay everywhere.\n";
  else
    return "Surprisingly there is no garbage around, as if someone cleaned here.\n";
}
