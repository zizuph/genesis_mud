/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

void create_menzo_room()
{
	set_short("Along the southeastern mantle of Donigarten");
	set_long(short() + ". The road runs northwest and southeast. It follows " +
        "the mantle which surround the city. The lake to the northwest " +
        "looks dark and forbidding with the island in the center. Lichens " +
        "and mosses grow in cultivted beds along the pond.");

    add_all_rooms();
    add_mantle();
    add_houses();
    add_donigarten_descr();
    
    reset_room();

    add_exit("road45", "northeast");
    add_exit("road60", "southwest");
    add_exit("warr01", "down");
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
