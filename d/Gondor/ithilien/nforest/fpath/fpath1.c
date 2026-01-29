/*
 *      /d/Gondor/ithilien/nforest/fpath/fpath1.c
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
    set_areadesc("green-shadowed woodlands");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress ");
    set_extraline("You are walking under old trees in ever-green woods. " +
        "Above you dark leaves form a polished roof in which many birds " +
        "are singing. An ever-present sweet and pungent smell of herbs " +
        "and flowers dominates in Ithilien, the garden of Gondor.");

    set_up_herbs( ({ HERB_DIR + "astaldo", HERB_DIR + "chervil",
		     HERB_DIR + "savory",  HERB_DIR + "hemlock", }),
		  ({ "ground", "field", "flowers", "forest", }), 3);

    add_item(({"mountains","mountain-range","mountain","ephel duath"}), 
        BSN("From here the mountains named Ephel Duath appear as dark " +
        "grey shadows beyond the stony ridges to the east. "+
        "You guess they are several miles away now."));
    add_item(({"forest", "wood", "woodlands", "herbs", "thicket"}),
        BSN("Many great trees are growing here, planted long ago, "
            + "falling into untended age amid a riot of careless "
            + "descendants. There are cedars and giant oaks and hoary "
            + "ash trees. Many herbs of different forms and scents "
            + "fill the air with sweet and pungent smells."));

    add_exit(ITH_DIR + "nforest/bank",         "northeast", 0, 3);
    add_exit(ITH_DIR + "nforest/fpath/fpath2", "west",      0, 3);
}

private string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}
