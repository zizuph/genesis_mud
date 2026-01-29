inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"
#include "wbt.h"

void
reset_room()
{
	::reset_room();
	bring_room_team(WWORK+"guard.c", 1, 2, WWORK+"guard.c", 1);
}

void
create_room()
{
	set_short("Guard's room");
   set_long("This is the simple room that acts as quarters "
	+"for the guards of the school.  The furniture here is "
	+"all well made, if not simple and fills its role "
	+"quite nicely.  Against the far wall, three small "
	+"beds are aligned for the guards.  In addition to that "
	+"there is a rack with some weapons on it and a small "
    +"table which can be used for meals or to play cards on.\n");
   add_item("table","This small table seems to be constructed out "
	+"of a combination of wood and bones.  Sitting "
	+"in the center of the table is a deck of cards.\n");
   add_item("rack","This is a simple rack with a few weapons "
	+"that the guards use on it.\n");
   add_item("weapons","There are a variety of simple weapons "
	+"on the rack.\n");
   add_item(({"bed","beds"}),"These simple beds look to be made "
	+"of wood.  Very simple beds, but they do their job well.\n");
   add_item("furniture","You see some beds, a rack for weapons "
	+"and a table.\n");
   add_item(({"cards","deck","deck of cards"}),"This deck "
	+"of cards is fairly normal looking, 52 cards with "
	+"various pictures of people and monsters on them.\n");
	INSIDE;

   add_exit(WWORK+"bar1.c", "west");
	set_alarm(1.0,0.0,"reset_room");
}

