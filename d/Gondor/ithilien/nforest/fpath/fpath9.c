/*
 *      /d/Gondor/ithilien/nforest/fpath/fpath9.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public int
hedge()
{
    write("You pass through the small gap in the row of hedges, " +
	  "carefully avoiding sharp thorns.\n");
    return 0;
}

public int
hollow()
{
    write("Following a shallow hollow, you walk towards the forest's edge.\n");
    return 0;
}

public void
create_area_room()
{
    set_areatype(3);
    set_areadesc("green fields");
    set_area("western");
    set_areaname("North Ithilien");
    set_land("Gondor");
    set_treetype("ash");
    set_extraline("Scattered across the fields are groups of trees " +
        "and bushes. To the west, you can see a dense hedge. To the " +
        "east, green-shadowed forests seem to extend forever, covering " +
        "steep slopes that rise towards the dark mountain-range at the " +
        "eastern horizon. An ever-present sweet and pungent smell of " +
        "herbs and flowers dominates in Ithilien, the garden of Gondor.");

    set_up_herbs( ({ HERB_DIR + "basil",   HERB_DIR + "foxglove", 
		     HERB_DIR + "redweed", HERB_DIR + "tarragon", }), 
		 ({ "ground", "field", "fields", "flowers", "forest"}), 3);
    add_item(({"mountains","mountain-range","mountain","ephel duath"}), BSN(
        "The mountains named Ephel Duath appear to be dark grey from here. "+
        "You can make them out just barely as dark shadows on the eastern horizon, " +
        "rising above the green slopes that lie between them and the field where " +
        "you are standing. You guess the mountains are many miles away from here."));
    add_item(({"forest","wood","woodlands"}), BSN(
        "The edge of the forest is not far to the east. The " +
        "green-shadowed woodlands cover the steep slopes that rise " +
        "towards the dark mountain range at the eastern horizon."));
    add_item(({"field","fields","bushes","herbs","thicket"}), BSN(
        "Scattered across the fields are groups of trees and bushes. " +
        "You can make out many ash trees and an occasional oak or " +
        "willow. At the feet of the trees, many bushes are thriving. " +
        "Many herbs of different forms and scents fill the air with " +
        "sweet and pungent smells."));
    add_item( ({ "hedge", "hedges", }), BSN(
        "A long row of hedges blocks the view to the east. It is almost " +
        "impenetrable, but you can make out a small gap in the hedge " +
        "where you might be able to pass."));

    add_exit(ITH_DIR + "nforest/fpath/fpath8", "southeast", hollow, 4);
    add_exit(ITH_DIR + "road/rr6",             "west",      hedge,  4);
}

public string
short_desc()
{
    return CAP(areadesc) + " in the " + area + " parts of " + areaname;
}

