/*
 * 4jail.c
 * Jail Cell in the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

create_cave()
{
  object door, prisoner;
  
  set_short("Prison Cell");
  set_long("   You are in a foul-smelling, disgusting environment. The "+
	   "floor of this prison cell is raw, uncut cave floor with "+
	   "jagged, sharp points. The walls are lined with an assortment "+
	   "of torture devices, most of which are bladed implements. Rancid, "+
	   "vile flesh droops down from the tips of the points of some "+
	   "of the blades and barbed points. Your first instinct upon "+
	   "entering this room is to leave immediately. You cannot avoid "+
	   "the smell of rancid flesh and the stench accompanied by "+
	   "keeping prisoners in a cell without cleaning them.\n\n");

  add_item(({"torture devices","devices","assortment"}),
	   "The torture devices all show signs of frequent use, "+
	   "including the presence of rotten flesh.\n");
  add_item(({"flesh","rotten flesh","rancid flesh"}),
	   "You are certain that the putrid flesh is what "+
	   "gives this prison its sweet aroma.\n");
  add_item(({"walls","wall"}),
	   "The rough, chiseled walls are decorated with an assortment "+
	   "of hanging torture devices.\n");
  add_item(({"points","barbed points","spike","spikes",
	       "blade","blades"}),
	   "Some of the barbs just refused to let go of thir victims.\n");
  
  add_prop(ROOM_I_INSIDE, 1);

  add_exit(THIS_DIR + "5jail", "west");
  
  seteuid(geteuid());
  door = clone_object(THIS_DIR+"obj/pdoor4b");
  door->move(this_object());

  prisoner = clone_object(THIS_DIR+"npc/prisoner3");
  prisoner ->move_living("into a room",TO);
}
