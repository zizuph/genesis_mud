/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

void create_menzo_room()
{
	set_short("Along the southern mantle of Donigarten");
	set_long(short() + ". The road runs west and northeast past carved " +
        "stalagmites and stalactites. A large pond is set in the center of " +
        "the area with a small island in the center. Mosses grow thickly " +
        "in beds along the pond.\n");

    add_all_rooms();
    add_mantle();
    add_houses();
    add_donigarten_descr();
    
    reset_room();

    add_exit("road59", "west");
    add_exit("road52", "northeast");
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
