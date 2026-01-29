#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object *crow = allocate(2 + random(3));

public void
create_area_room()
{
    int     i, s,
	    seed;
    string  name = explode(file_name(TO), "/")[5];

    set_areatype(7);
    set_areadesc("green-shadowed woodland");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline("To the west, light shines through the trees, as if "
       + "the forest came to a sudden end, at a brink looking out only "
       + "on to sky. Far beyond, hidden in clouds and mists, the river "
       + "Anduin can be seen. An ever-present sweet and pungent smell "
       + "of herbs and flowers dominates in Ithilien, garden of Gondor.");

    for (i = 0, s = strlen(name); i < s; i++)
	seed += name[i];

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("ithilien"), seed),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("middle earth"), seed + 1),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), seed + 2), }),
                  ({ "ground", "field", "flowers", "forest", }), 3);
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item(({"forest","wood","woodlands","herbs","thicket"}), BSN(
        "Many great trees are growing here, cedars and giant oaks "
      + "and hoary ash trees. Many herbs of different forms and scents "
      + "fill the air with sweet and pungent smells."));
    add_item(({"brink", "forest edge", "edge", }), BSN(
        "Just west of here is an edge where the land falls into the great "
      + "vales. The edge continues to the south, sometimes falling suddenly "
      + "and sheer, like it does here, sometimes in long hillsides."));
    add_item(({"anduin", "great vales", "vales", "river", }), BSN(
        "Far west, beyond the vales that stretch from the brink of the "
      + "hills towards to bank of the river, the river Anduin itself can "
      + "be seen, flowing gently southwards, like a broad band of blue "
      + "dividing the green lands on both banks."));
    add_exit(ITH_DIR + "nforest/fpath/fpath6", "north", 0, 4);
    add_exit(ITH_DIR + "nforest/forest2",      "south", 0, 4);

    reset_room();
}

string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

public void
clone_crow()
{
    int     i, s;

    for (i = 0, s = sizeof(crow); i < s; i++)
        if (!objectp(crow[i]))
        {
            crow[i] = clone_object(NPC_DIR + "crow");
	    crow[i]->set_restrain_path(ITH_DIR + "nforest");
	    crow[i]->set_random_move(5);
	    crow[i]->move_living("down", TO);
	    set_alarm(30.0 + rnd() * 60.0, 0.0, clone_crow);
	    return;
	}
}

public void
reset_room()
{
    set_searched(-2);

    set_alarm(30.0 + rnd() * 60.0, 0.0, clone_crow);
}

