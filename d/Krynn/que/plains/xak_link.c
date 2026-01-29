#include "local.h"
inherit "/d/Krynn/std/outside_room";

void
create_krynn_room()
{
    set_short("On a small hill");
    set_long("You are standing on a small hill overlooking a nasty, gloomy " +
	     "looking swamp to your northeast. Mist is floating through the " +
	     "boughs of the low and dark trees so you cannot make out any details " +
	     "nor how far it stretches. You can reach the border of the swamp by " +
	     "following the small path to the east. Towards your west and south, " +
	     "further hills covered by much lighter trees can be seen. Directly " +
	     "to the south, you see a small valley where travel is easily possible.\n");
    add_item(({"swamp","hill","hills","boughs","trees","path"}),
	     "You cannot see anything special about it.\n");
    
    add_exit(TDIR+"rooms/plain-21-11-h",  "west", 0, 4, 1);
    add_exit(TDIR+"rooms/plain-22-12-3", "south", 0, 3);
    add_exit(XAK_CITY, "east");
}
