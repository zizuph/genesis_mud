/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

string extra_line = "Waves lap against the isle in the large pond.";

void create_menzo_room()
{
	set_short("Along the eastern mantle of Donigarten");
	set_long(menzo_descr6(extra_line));

    add_all_rooms();
    add_mantle();
    add_houses();
    add_donigarten_descr();
    
    reset_room();

    add_exit("road26", "north");
    add_exit("road45", "south");
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
