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
	set_short("Along the northern mantle between Eastmyr and the Braeryn");
	set_long(menzo_descr6(extra_line));

    add_all_rooms();
    add_mantle();
    add_houses();
    reset_room();

    add_exit("road25", "east");
    add_exit("road14", "northwest");
    add_exit("road34", "southwest");
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
