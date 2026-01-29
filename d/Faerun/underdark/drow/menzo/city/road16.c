/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

void create_menzo_room()
{
	set_short("Along the northeast mantle of Donigarten");
	set_long(short() + ". A large pond dominates the area. An isle rises " +
        "from the center of it. Large stands of tall mushrooms block your " +
        "view of most of the area.\n");

    add_all_rooms();
    add_mantle();
    add_houses();
    add_donigarten_descr();
    
    reset_room();

    add_exit("road17", "east");
    add_exit("road15", "west");
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
