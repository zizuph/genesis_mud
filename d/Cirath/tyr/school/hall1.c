#include "/d/Cirath/common/defs.h"
inherit "/std/room";
#include "wbt.h"

void
create_room()
{
	set_short("Hall");
   set_long("You are standing in a long hallway that "
	+"stretches out towards the training hall to the "
	+"east, and towards the stairs down to the training "
	+"square to the west.  You hear loud voices and "
	+"clattering weapons to the east as well.\n");
   add_item("hallway","It is long and runs east and west.\n");
   add_item("stairs","They are to the west.\n");

	INSIDE;

	add_exit(WWORK+"b1.c", "west", 0, 0);
	add_exit(WWORK+"hall2.c", "east", 0, 0);
}

