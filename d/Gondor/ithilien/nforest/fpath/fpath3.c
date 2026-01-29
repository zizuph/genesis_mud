/*
 *      /d/Gondor/ithilien/nforest/fpath/fpath3.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

static object  Deer;

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("green-shadowed woodlands");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("You are walking under old trees in ever-green woods. " +
        "The woodlands seem to extend forever in every direction, and " +
        "they are gently falling down towards the west. Through the " +
        "trees to the north you can sometimes glimpse a forest stream. " +
        "An ever-present sweet and pungent smell of herbs and flowers " +
        "dominates in Ithilien, the garden of Gondor.");

    set_up_herbs( ({ HERB_DIR + "attanar", HERB_DIR + "fennel", 
		     HERB_DIR+"oregano", }), 
		  ({ "ground", "field", "flowers", "forest", }), 3);

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item(({"forest","wood","woodlands","herbs","thicket"}), BSN(
        "Many great trees are growing here, cedars and giant oaks and " +
        "hoary ash trees. Many herbs of different forms and scents fill " +
        "the air with sweet and pungent smells."));
    add_item(({"river", "stream", "water"}), BSN(
        "From time to time you can see a band of water through the " +
        "trees. The stream seems to run down the slopes westwards to " +
        "join the Anduin down in its vale."));

    add_exit(ITH_DIR + "nforest/fpath/fpath2", "east",      0, 4);
    add_exit(ITH_DIR + "nforest/fpath/fpath4", "southwest", 0, 4);

    reset_room();
}

static string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

public void
reset_room()
{
    ::reset_room();

    Deer = clone_npc(Deer, NPC_DIR + "deer", ITH_DIR + "nforest/fpath/");
}
