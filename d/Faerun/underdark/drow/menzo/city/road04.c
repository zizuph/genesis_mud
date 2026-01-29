/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

string extra_line = "To the north is Tier Breche.";

void create_menzo_room()
{
	set_short("Along the Northern Mantle");
	set_long(menzo_descr1(extra_line));

    add_all_rooms();
    add_mantle();
    add_houses();
    reset_room();


    add_exit("road03","west");
    add_exit("road08", "southeast");

        
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
