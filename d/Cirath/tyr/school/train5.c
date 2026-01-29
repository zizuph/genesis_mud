inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"
#include "wbt.h"

void
reset_room()
{
	::reset_room();
	bring_room_team( WWORK+"adv.c", 1, 3, WWORK+"adept.c", 1);
}

void
create_room()
{
   set_short("Corner of Training Hall");
   set_long("This is the corner of the training hall that is "
	+"dedicated to the training of defence.  Unlike most "
	+"other parts of the training hall, there are no weapon "
	+"racks or practice dummies here, just bare stone walls "
	+"and floors.  In fact the only thing you do see here "
	+"are a few torches on the walls to provide light.\n");
   add_item(({"torch","torches"}),"They are hanging on the wall "
	+"and are giving a warm glow to the room.\n");
	INSIDE;

	add_exit(WWORK+"train3.c", "south", 0, 0);
	add_exit(WWORK+"train2.c", "east", 0, 0);
	set_alarm(1.0,0.0,"reset_room");
}
