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
    set_long("The muddy road passes through the camp. It is well travelled " +
        "and passes between rows of tents and under trees.\n");

    add_exit(ITH_DIR+"forest/haradcamp4s", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp11s", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp9s", "east", 0);
    add_exit(ITH_DIR+"forest/haradcamp7s", "west", 0);


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
