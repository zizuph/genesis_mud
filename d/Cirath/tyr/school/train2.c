inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"
#include "wbt.h"

void
reset_room()
{
	::reset_room();
	bring_room_mob("rasin", WWORK+"gt.c", 1, 1);
}

void
create_room()
{
   set_short("Center of Training Hall");
   set_long("This is the central room in the large hall that "
	+"the school uses for training.  This area looks "
	+"identical to the rest of the training area, save "
	+"the large chair sitting against the northern wall.  "
	+"Usually one of the school's instructors sits in the "
	+"chair to watch over the students, and to occasionally "
	+"show the adepts new tactics or correct their mistakes.\n");
   add_item(({"chair","large chair"}),"This large wooden chair "
	+"looks to be made of simple pieces of wood crafted "
	+"together to create almost a perch above the room.  "
	+"It sits a few feet above the floor and thus provides "
	+"the instructors a vantage point to look at the students "
	+"training.\n");

	INSIDE;

	add_exit(WWORK+"train1.c", "south", 0, 0);
	add_exit(WWORK+"train5.c", "west", 0, 0);
	add_exit(WWORK+"train6.c", "east", 0, 0);
	set_alarm(1.0,0.0,"reset_room");
}

