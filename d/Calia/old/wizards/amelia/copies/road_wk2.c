inherit "/std/room";
#include <macros.h>
#include "/d/Calia/overlord/defs.h"
inherit SLIP;

void
create_room()
{
    set_short("Crystalline road");
    set_long(BS(
	"You are on a slippery crystalline road.  " +
        "Something seems to be compelling you to take a closer look " +
        "at an odd-looking tree just off of the road.  " +
	"\n"));
    add_item("tree","The bark on this tree has begun to crystallize.\n");
    add_exit(ROAD+"rooms/road_wk1", "north", "@@slip");
    add_exit(ROAD+"rooms/road_wk3", "south", "@@slip");
}
