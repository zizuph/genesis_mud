#include "/d/Cirath/common/defs.h"
inherit "/std/room";
#include "wbt.h"

void
create_room()
{
	set_short("In the hall of Great Warrior's school");
   set_long("You have arrived at an intersection in the hall. "
	+"A set of large wooden doors, slightly ajar, lie to "
	+"the north, as well as an ornate hardwood door to the "
	+"south.  The southern door has an inscription above it "
	+"which appears to be readable.  The hall also continues "
	+"stretching out east and west.\n");
   add_item("hall","You are inside of it, and it stretches to "
	+"both the east and west.\n");
   add_item("door","Which one do you want to look at?  The "
	+"hardwood door or the large wooden door?\n");
   add_item("hardwood door","This door is made from some "
	+"type of wood that is very hard, but also looks "
	+"very expensive.  There is an inscription above "
	+"the door.\n");
   add_item(({"large door","wooden door","large wooden door"}),
	"This door is made from some cheap, old wood that has "
	+"obviously been around for quite a while.  After "
	+"peering into the room behind it, you discover that "
	+"the door leads to the training hall.\n");
   add_item("inscription","It is above the ornate hardwood "
	+"door to the south and appears to be readable.\n");
   add_cmd_item("inscription","read","The sign says:\n "+
    "Dormitories.\n");
	INSIDE;

	add_exit(WWORK+"train1.c", "north", 0, 0);
	add_exit(WWORK+"bar1.c", "south", 0, 0);
	add_exit(WWORK+"hall1.c", "west", 0, 0);
	add_exit(WWORK+"hall3.c", "east", 0, 0);
}
