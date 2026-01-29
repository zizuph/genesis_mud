/*
 *      /d/Gondor/ithilien/nforest/fpath/fpath8.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("at the edge of a forest");
    set_area("western");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("ash");
    set_extraline("You are in small cut between hills to the north and " +
        "the south. To the east, the ridge continues making a turn to " +
        "the left, gradually rising between the hills. The green-shadowed " +
        "woodlands covering the slopes seem to extend forever in every " +
        "direction but to the west. There green fields with scattered " +
        "groups of trees and bushes stretch towards a row of hedges. " +
        "An ever-present sweet and pungent smell of herbs and flowers " +
        "dominates in Ithilien, the garden of Gondor.");

    set_up_herbs( ({ HERB_DIR + "caraway", HERB_DIR + "foxglove", 
		     HERB_DIR + "savory",  HERB_DIR + "suranie", }),
		 ({ "ground", "field", "flowers", "forest", "woodlands"}), 3);
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item( ({"forest","wood","woodlands","herbs","thicket"}), BSN(
        "Many great trees are growing here, mostly giant oaks, but cedars " +
        "and hoary ash trees, too. Many herbs of different forms and " +
        "scents fill the air with sweet and pungent smells."));
    add_item( ({"field","fields","bushes","herbs","thicket"}), BSN(
        "Scattered across the fields are groups of trees and bushes. " +
        "You can make out many ash trees and an occasional oak or " +
        "willow. At the feet of the trees, many bushes are thriving. " +
        "Many herbs of different forms and scents fill the air with " +
        "sweet and pungent smells."));
    add_item(({"hedge"}), 
        "Beyond the fields, a long row of hedges blocks the view to the east.\n");

    add_exit(ITH_DIR + "nforest/fpath/fpath7","northeast",0,5);
    add_exit(ITH_DIR + "nforest/fpath/fpath9","northwest",0,4);
}

public string
short_desc()
{
    return CAP(areadesc) + " in the "+area+" parts of "+areaname;
}
