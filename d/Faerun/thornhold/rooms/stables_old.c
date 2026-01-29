/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
//#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit "/d/Gondor/common/lib/drink_water.c";
inherit BASE_KEEP;

void
create_house()
{
	add_prop(ROOM_I_ALLOW_STEED, 1); // It's a stable so make an exception

    set_short("The Thornhold Stables");
    set_long("You are in the Thornhold stables. Dappled light spills in " +
             "from the courtyard, through spaces in the wooden planks that " +
             "were used to construct the stable entrance. In contrast, " +
             "the ceiling and exterior walls are constructed of the same " +
             "sturdy gray stone of the rest of the hold. A thick layer of " +
             "hay blankets the floor here, and several box stalls with " +
             "feeding and watering troughs for horses, ponies, and mules " +
             "currently in the care of the dwarves of Thornhold. You " +
             "can enter a farrier's workshop to the north, or return " +
             "west to the courtyard.\n");

	add_item("hay",
        "Hay blankets the floor here in a thick layer. It's clean, " +
        "and clearly the stable is well-tended.\n");

    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    set_drink_from( ({ "trough", "water"}) );
	
    add_exit(ROOM_DIR + "courtyard_south",  "west");
    add_exit(ROOM_DIR + "farrier",  "north");

    reset_room();
}

void
reset_room()
{
   ::reset_room();
}

public void
init()
{
    ::init();
// This initializes the drink function.
    init_drink();
}

