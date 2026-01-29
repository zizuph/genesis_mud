#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  fox;

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
    set_treetype("ash");
    set_extraline("The edge of the forest skirts a sheer cliff running "
      + "from north to south just west of here. Beyond the brink lie the "
      + "great vales of Ithilien, which open onto the bank of the Anduin. "
       + "An ever-present sweet and pungent smell "
       + "of herbs and flowers dominates in Ithilien, garden of Gondor.");

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item(({"forest","wood","woodlands","herbs","thicket"}), BSN(
        "Many great trees are growing here, cedars and giant oaks "
      + "and hoary ash trees. Many herbs of different forms and scents "
      + "fill the air with sweet and pungent smells."));
    add_item(({"brink", "forest edge", "edge", "cliff", }), BSN(
        "Just west of here is an edge where the hill country ends in a sheer "
      + "cliff, falling down to the great vales. The edge continues to the "
      + "south and to the north, sometimes falling suddenly and sheer, "
      + "sometimes in long hillsides."));
    add_item(({"anduin", "great vales", "vales", "river", }), BSN(
        "Far west, beyond the vales that stretch from the brink of the "
      + "hills towards to bank of the river, the river Anduin itself can "
      + "be seen, flowing gently southwards, like a broad band of blue "
      + "dividing the green lands on both banks."));
    add_exit(ITH_DIR + "nforest/forest1",       "north", 0, 4);
    add_exit(ITH_DIR + "nforest/fpath/fpath42", "east",  0, 4);
    add_exit(ITH_DIR + "nforest/forest3",      "south", 0, 4);

    for (i = 0, s = strlen(name); i < s; i++)
	seed += name[i];

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("ithilien"), seed),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("middle earth"), seed + 1),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), seed + 2), }),
                  ({ "ground", "field", "flowers", "forest", }), 3);

    reset_room();
}

string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

public void
reset_room()
{
    object  clock = find_object(CLOCK);

    set_searched(-2);

    if (clock->query_war())
	return;

    if (objectp(fox))
	return;

    fox = clone_object(NPC_DIR + "fox");
    fox->set_restrain_path(ITH_DIR + "nforest/");
    fox->set_random_move(5);
    fox->set_whimpy(50);
    fox->move_living("down", TO);

}

