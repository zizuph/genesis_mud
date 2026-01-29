/*
 * Southern end of the Haradrim camp
 * -- Finwe, August 2005
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include "/d/Gondor/defs.h"

static object	*Haradrim = allocate(3);
object	Oli;

public void
create_camp()
{
    set_short("In the southern part of the Haradrim camp");
    set_long("Muddy paths run south and east through the camp. North is " +
        "a dirty river that runs east and west past tents that line it " +
        "and the road. Piles of dung lay alongside the road just on " +
        "the edge of the forest. There is a large pen here.\n");


    add_exit(ITH_DIR+"forest/haradcamp10s", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp5s", "west", 0);

    reset_room();

    add_harad_camp_tells();
    set_add_forest();
    set_add_dung();
    set_add_river();
    set_tall_tents();
    set_oli_pens();
}

public void
reset_room()
{
    ::reset_room();
    make_haradrim(random(3));
    Oli = clone_npc(Oli, (NPC_DIR + "mumak"));
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
