/*
 *      /d/Gondor/ithilien/nforest/fpath/fpath5.c
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
    set_extraline("The woodlands are thinner here than further east, " +
        "and the land is falling more steeply down towards the Anduin. " +
        "To the north, a thicket of bushes blocks your path and your " +
        "view. Above you dark leaves form a polished roof in which many " +
        "birds are singing. An ever-present sweet and pungent smell of " +
        "herbs and flowers dominates in Ithilien, the garden of Gondor.");
    set_up_herbs( ({ HERB_DIR + "dill", HERB_DIR + "saffron", 
		     HERB_DIR + "ungolestel" }), 
		 ({ "ground", "field", "flowers", "forest", "woodlands", }), 3);

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item(({"forest","wood","woodlands","herbs","thicket"}), BSN(
        "Many great trees are growing here, cedars and giant oaks and " +
        "hoary ash trees. Many herbs of different forms and scents " +
        "fill the air with sweet and pungent smells."));
    add_item(({"thicket","bush","bushes"}), BSN(
        "A dense thicket of bushes extends north of here. Some of the " +
        "bushes are thorny, and the interleaving branches of the bushes " +
        "prevent you from going north. "));

    add_exit(ITH_DIR + "nforest/fpath/fpath4","east",0,4);
    add_exit(ITH_DIR + "nforest/fpath/fpath6","west",0,4);
}

public string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}
