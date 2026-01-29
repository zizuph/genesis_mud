/*
 * Northern side of the Haradrim camp
 * -- Finwe, July 2005
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include "/d/Gondor/defs.h"

static object	*Haradrim = allocate(1 + random(2));

public void
create_camp()
{
    set_short("A well travelled road in the Ithilien forest");
    set_long("The forest surrounds you as you travel this way. The road is " +
        "wide appears well used.\n");
    add_item("forest", 
        "The forest extends in all directions, hiding all activity and " +
        "muffling the sounds.\n");
    add_item("road",
	    "The road runs north and south through the forest. It seems to be well " +
        "used.\n");

    add_exit(ITH_DIR+"forest/haradpath1", "north", 0);
    add_exit(ITH_DIR+"forest/haradpath3", "south", 0);

    reset_room();

//    add_harad_camp_tells();
}

public void
reset_room()
{
    ::reset_room();
//    clone_npcs(Haradrim, NPC_DIR+"haradrim", -1.0);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
