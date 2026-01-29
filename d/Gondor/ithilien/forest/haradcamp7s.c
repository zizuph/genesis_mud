/*
 * Southern end of the Haradrim camp
 * -- Finwe, August 2005
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include "/d/Gondor/defs.h"

static object	*Haradrim = allocate(3);

public void
create_camp()
{
    set_short("In the Haradrim part of the camp");
    set_long("Broken branches hand down from the forest where great " +
        "animals have twisted them off. The muddy road runs north and " +
        "east past rows of neat tents. Flies swarm up and buzz around " +
        "your head, then settle down on piles of dung alongside the road. " +
        "A large tent has been set up here.\n");

    add_exit(ITH_DIR+"forest/haradcamp3s", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp8s", "east", 0);

    add_cmd_item("large tent", "enter", enter_tent);
    set_tent_path(ITH_DIR+"forest/haradtent7s");

    reset_room();

    add_harad_camp_tells();
    set_add_forest();
    set_add_dung();
    set_tall_tents();
}

public void
reset_room()
{
    ::reset_room();
    make_haradrim(random(3));
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
