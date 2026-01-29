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
    set_long("Broken branches hang from trees. The forest has been " +
        "cleared but forms a border around the camp. The muddy paths " +
        "lead through the camp and past piles of animal dung. It smells " +
        "and has flies swarming around them. A large pen is here.\n");

    add_exit(ITH_DIR+"forest/haradcamp6s", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp13s", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp9s", "west", 0);

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
    make_haradrim(random(4));
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
