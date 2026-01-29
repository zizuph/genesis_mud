/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

string extra_line = "Seedier Drow live visit and live here.";

void create_menzo_room()
{
	set_short("Along the northern mantle");
	set_long(menzo_descr4(extra_line));

    add_all_rooms();
    add_mantle();
    add_houses();
    reset_room();

    add_exit("road14","east");
    add_exit("road09", "northwest");
    add_exit("road23", "southwest");       
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
