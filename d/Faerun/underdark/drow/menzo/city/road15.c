/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

string extra_line = "A small island rises from a large pond to the south.";

void create_menzo_room()
{
	set_short("Along the northeast mantle near Donigarten");
	set_long(menzo_descr2(extra_line));

    add_all_rooms();
    add_mantle();
    add_houses();
    add_donigarten_descr();
    
    reset_room();

    add_exit("road16", "east");
    add_exit("road25", "southwest");
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
