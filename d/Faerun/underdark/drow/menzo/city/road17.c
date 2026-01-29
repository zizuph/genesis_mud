/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

void create_menzo_room()
{
	set_short("Along the eastern mantle of Donigarten");
	set_long(short() + ". Large stands of mushrooms grow nearby. The area " +
        "is empty except for the road that passes by. Drow patrols wander " +
        "by, protecting the lichens, mosses, and mushrooms growing in the " +
        "area. A pond fills the area with a small isle rising out of it.\n");

    add_all_rooms();
    add_mantle();
    add_houses();
    add_donigarten_descr();
    
    reset_room();

    add_exit("road16", "west");
    add_exit("road26", "southeast");
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
