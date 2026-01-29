/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

string extra_line = "This large area of the city is where the common drow " +
    "live and work. Shops are open, offering their wares for sale. ";

void create_menzo_room()
{
	set_short("Along the northern mantle");
	set_long(short() + ". Buildingss crowd this area, where common Drow live and work. Shadows hide the more notorious aspects of the area. Shops of all kinds line the road.\n");

    add_all_rooms();
    add_mantle();
    add_houses();
    reset_room();


    add_exit("road08","west");
    add_exit("road13", "southeast");

        
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
