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
    set_short("In the southern part of the Haradrim camp");
    set_long("The road ends here. The forest has been cleared back " +
        "and hides tents that have been pitched round about. A dirty " +
        "smells wafts from the river north of here. There is a large tent " +
        "here.\n");

    add_exit(ITH_DIR+"forest/haradcamp3s", "east", 0);
    add_cmd_item("large tent", "enter", enter_tent);
    set_tent_path(ITH_DIR+"forest/haradtent2s");

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
