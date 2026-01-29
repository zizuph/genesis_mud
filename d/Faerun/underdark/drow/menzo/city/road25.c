/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

string extra_line = "Large fungi grow in groups everywhere. There is a small island in a lake to the east.";

void create_menzo_room()
{
	set_short("Along the northeast mantle near Donigarten");
	set_long(short() + ". Warm air blows past you. It blows from unknown " +
        "vents. Large stands of mushrooms grow neaerby. There is a large " +
        "pond to the southeast with a small island in the center.");

    add_all_rooms();
    add_mantle();
    add_houses();
    add_donigarten_descr();
    
    reset_room();
    
    add_exit("road35", "south");
    add_exit("road24", "west");
    add_exit("road15", "northeast");

}

void
init()
{
    ::init();
}

void
reset_room()
{
}
