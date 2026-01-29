/*
 * Village elder tent
 * TAPAKAH 05/2005
 */

#pragma strict_types

inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"
#include "../../nspeir.h"
#include "../../village/village.h"

object elder;
object servant;
object chest;

void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Elder's tent in " + VILLAGENAME);
  set_long(BS("You are inside the tent of the elder of " + VILLAGENAME + " "+
	      "It is very spartan here, but tidy. There is a small cot and a locked chest. " +
	      "A set of skulls is forming a line, and a few papers with sketches on them " +
	      "are in the corner. There is also a set of bottles near the entrance. "));
  add_exit("crossing","out",0);
  add_item(({"cot"}),
	   "The cot is obviously for both sleeping and sitting of the elder.\n");
  add_item(({"skull","skulls"}),
	   "The skulls look at you with their empty eyesockets.\n");
  add_item(({"bottles","bottle"}),
	   "They are quite dusty and have a repulsive smell and you really do not want to touch them.\n");
  add_item(({"paper","papers","sketch","sketches"}),
	   "They have some indistinguishable drawings and writings on them.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(GV_OUTSIDE,0);
  reset_room();
}

void
init()
{

  ::init();
}

void
reset_room()
{
  ::reset_room();
  if(!chest) {
    chest = clone_object(CHEST);
    chest->move(TO);
  }
  if(!servant) {
    servant = clone_object(ESERVANT);
    servant->move_living("X",TO);
  }
  if(!elder) {
    elder = clone_object(ELDER);
    elder->move_living("X",TO);
  }
}
