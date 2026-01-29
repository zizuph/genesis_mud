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
	set_short("Along the northern mantle");
	set_long(menzo_descr5(extra_line));

    add_all_rooms();
    add_mantle();
    add_houses();
    reset_room();

    add_exit("road13","west");
    add_exit("road24", "southeast");
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
