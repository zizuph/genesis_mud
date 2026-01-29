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
    set_short("north side of the bridge");
    set_extraline("The road heads north towards the city and south across " +
	"the stone bridge. " +
	"There is a faint, unrecognizable scent in the air, irritating your senses " +
	"with each windblow from the north. The road is empty and looks as if it has " +
	"been days since it was last travelled.\n");

    add_features(({"bridge", "nw_city_n_far", "river",
    	"highroad", "neverwinterf", "grasslands"}));
    
    reset_faerun_room();

    add_exit(BR_DIR + "nrd09", "north");
    add_exit(BR_DIR + "bri00", "south");

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


