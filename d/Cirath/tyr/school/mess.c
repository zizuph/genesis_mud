inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"
#include "wbt.h"

void
reset_room()
{
	bring_room_mob("alteer", WWORK+"captain.c", 1, 1);
}


void
create_room()
{
	set_short("In the school's mess");
   set_long("You are now in the school's mess hall.  The "
	+"room is long and narrow and filled with a few tables "
	+"with benches or chairs to sit on.  You can smell "
	+"something wafting in from the north, and it is "
	+"not a pleasant thing.\n");
   add_item(({"tables","table"}),"There are three seperate "
	+"tables here, one long one for the students, one "
	+"medium size one for the guards, and a small table "
	+"for the instructors.\n");
  add_item(({"chairs","chair"}),"The only table with chairs "
	+"is the one for the instructors, everyone else must "
	+"sit on benches.\n");
   add_item(({"bench","benches"}),"The benches are long and "
	+"look very uncomfortable.  They look to be made "
	+"from a combination of bone and wood.\n");

	INSIDE;

	add_exit(WWORK+"hall3.c", "southwest", 0, 0);
	set_alarm(1.0,0.0,"reset_room");
}
