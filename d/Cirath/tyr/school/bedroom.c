inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"
#include "wbt.h"

void
reset_room()
{
	::reset_room();
	bring_room_team(WWORK+"adv.c", 1, 2, WWORK+"adept.c", 1);
}

void
create_room()
{
     set_short("Adept Barracks");
   set_long("This is the main barracks for the adept level "
	+"students of the the Warrior's School.  There are simple "
	+"bunk beds lining the walls.  After a long days work in the "
	+"training hall, this is where the students come for "
	+"rest.  There are two torches on the wall offering "
	+"some light to see by, but it is still fairly dim here.\n");
   add_item(({"bed","beds","bunk beds","bunk bed"}),
	"These are simple wooden beds with thin mattresses. "
	+"While not exactly lavish, they are better than "
	+"sleeping on the floor.\n");
   add_item(({"torch","torches"}),"There are two of them on "
	+"the walls here, providing minimal light.\n");
	INSIDE;

	add_exit(WWORK+"hall3.c", "northwest", 0, 0);
	set_alarm(1.0,0.0,"reset_room");
}
	
