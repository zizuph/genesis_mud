/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

string extra_line = "";

void create_menzo_room()
{
	set_short("Along the eastern mantle of Donigarten");
	set_long(short() + ". The road passes around carved stalagmites. They " +
        "rise from the ground and are limned in faerie fire. Warm air blows past you. It is stifling and smells stale.");

    add_all_rooms();
    add_mantle();
    add_houses();
    add_donigarten_descr();
    
    reset_room();

    add_exit("road36", "south");
    add_exit("road17", "northwest");
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
