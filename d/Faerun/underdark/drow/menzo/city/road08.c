/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

string extra_line = "This large area of the city is where the common drow " +
    "live and work. Shops are open, offering their wares for you. ";

void create_menzo_room()
{
	set_short("Along the northern mantle");
	set_long(menzo_descr2(extra_line));

    add_all_rooms();
    add_mantle();
    add_houses();
    reset_room();


    add_exit("road09","east");
    add_exit("road04", "northwest");

        
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
