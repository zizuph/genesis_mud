/*
 * Southern end of the Haradrim camp
 * -- Finwe, August 2005
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include "/d/Gondor/defs.h"


public void
create_camp()
{
    set_short("In the Haradrim part of the camp");
    set_long("Tall tents line the muddy road, which runs north, south, " +
        "east, and west. Broken branches hang from the trees above. Flies " +
        "swarm around piles of dung that lay scattered about the road. " +
        "There is a large tent set up here.\n");

    add_exit(ITH_DIR+"forest/haradcamp3", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp8s", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp5s", "east", 0);
    add_exit(ITH_DIR+"forest/haradcamp3s", "west", 0);

    add_cmd_item("large tent", "enter", enter_tent);
    set_tent_path(ITH_DIR+"forest/haradtent4s");

    reset_room();

    add_harad_camp_tells();
    set_add_forest();
    set_add_dung();
    set_add_river();
    set_tall_tents();
}

public void
reset_room()
{
    ::reset_room();
    make_haradrim(random(4));
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
