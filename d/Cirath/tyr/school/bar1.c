inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "wbt.h"

void
create_room()
{
   set_short("Guard and Teacher Barracks");
   set_long("You have entered the part of the school used as "
	+"the home for both the teachers and the guards that defend "
	+"them.  From the north, the noise of training students "
	+"is still audible.  You also hear sounds from both "
	+"the guard rooms to the east and west, and the "
	+"teachers quarters to the south.\n");

	INSIDE;

	add_exit(WWORK+"hall2.c", "north", 0, 0);
	add_exit(WWORK+"teach.c", "south", 0, 0);
	add_exit(WWORK+"g1.c", "west", 0, 0);
	add_exit(WWORK+"g2.c", "east", 0, 0);
}
