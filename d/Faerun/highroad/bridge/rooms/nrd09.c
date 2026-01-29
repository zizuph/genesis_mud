/*
 * The Northern end of the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

//inherit BASE_ROAD;
inherit "/d/Faerun/highroad/bridge/std/base_road.c";

void
create_road()
{
    set_short("just south from the Neverwinter gates");
    set_extraline("The road heads north where it reaches massive gates of Neverwinter " +
		"and south towards the river. " +
		"The foul smell is invading your senses making your eyes tingle and your stomach " +
		"sick. The road is empty and looks as if it has " +
		"been days since it was last travelled.\n");


    add_features(({"bridge", "nw_city_n_close", "river",
    	"highroad", "neverwinterf", "grasslands"}));

    reset_faerun_room();

    add_exit(BR_DIR + "nw_sgate", "north");
    add_exit(BR_DIR + "bri01", "south");

}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
}


