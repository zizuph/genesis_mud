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
    set_long("Branches hang over the muddy road as it passes beneath " +
        "them. The road runs in all directions in the camp and passes by " +
        "rows of tents. A large tent has been erected here.\n");

    add_exit(ITH_DIR+"forest/haradcamp5s", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp12s", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp10s", "east", 0);
    add_exit(ITH_DIR+"forest/haradcamp8s", "west", 0);

    add_cmd_item("large tent", "enter", enter_tent);
    set_tent_path(ITH_DIR+"forest/haradtent9s");

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
