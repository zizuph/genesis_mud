/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

string extra_line = "Moss beds grow alongside in the Donigarten.";

void create_menzo_room()
{
	set_short("Along the southeastern mantle of Donigarten");
	set_long(menzo_descr2(extra_line));

    add_all_rooms();
    add_mantle();
    add_houses();
    add_donigarten_descr();
    
    reset_room();

    add_exit("road45", "north");
    add_exit("road52", "southwest");
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
