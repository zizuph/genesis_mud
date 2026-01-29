#include "/d/Cirath/common/defs.h"
inherit "/std/room";
#include "wbt.h"

void
create_room()
{
   set_short("Northeast Corner of Training Hall");
   set_long("This part of the training hall appears to have been "
	+"designed to provide a specific place to train offensive "
	+"skills.  The adepts here are engaged in sparring and "
	+"from time to time you hear an adept yelp in pain as his "
	+"opponent lands a solid blow.  Plain stone walls and "
	+"floor are all that are here, aside from a few torches "
	+"sitting in sconces in the wall.\n");
   add_item(({"torch","torches"}),"They provide a nice amount "
	+"of light here, without there being too much smoke.\n");
   add_item(({"adept","adepts"}),"They look to be engaged in light "
	+"sparring.\n");

	INSIDE;

	add_exit(WWORK+"train4.c", "south", 0, 0);
	add_exit(WWORK+"train2.c", "west", 0, 0);
}
