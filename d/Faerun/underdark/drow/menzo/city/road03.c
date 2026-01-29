/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COMMON;

void create_menzo_room()
{
	set_short("Entrance to Tier Breche");
	set_long(short() + ". This is a great plaza in Menzobarranzan. Immense stalagmites and stalagtites are carved into massive columns. They mark the entrance to the Academy north of here. The columns are limned with faerie fire and glow in the subdued light.\n");

    add_all_rooms();
    add_mantle();
    add_houses();

    add_item(({"plaza", "large plaza"}),
        "It is a large circle set with black stones. An enormous image of a red spider fills the plaza. It seems to shift and move, watching your every move.\n");

    add_exit("", "north");
    add_exit("road07", "south");
    add_exit("road04","east");
    add_exit("road02", "west");

        
}

void
init()
{
    ::init();
}