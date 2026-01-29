/*
 * 7Jail.c
 * Hallway in Jail in Caverns
 * - Alaron January 1997
 */


inherit "/std/room.c";
#include "/sys/stdproperties.h"
#include "defs.h"

void
create_room()
{
   object door1,door2;

   set_short("Cavernous Passageway");
   set_long("   You are in a dark, damp and cold cave. The cave extends "+
	    "out to the north and southwest, leading further into "+
	    "the darkness surrounded by echos of dripping water where "+
	    "another door rests within the cave. The "+
	    "area here is dominated by a foul, almost sweet-smelling "+
	    "odor of rot and decay. It seems to be eminating from behind "+
	    "the cell door which is recessed into the east wall.\n\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_exit(THIS_DIR + "6jail", "north");
   add_exit(THIS_DIR + "2guardrm","southwest");
   add_exit(THIS_DIR + "8jail","east");

   seteuid(geteuid());
   door1 = clone_object(THIS_DIR+"obj/pdoor3a");
   door2 = clone_object(THIS_DIR+"obj/pdoor2b");
   door1 ->move(TO);
   door2 ->move(TO);
}
