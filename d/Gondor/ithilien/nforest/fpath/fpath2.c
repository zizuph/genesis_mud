/*
 *      /d/Gondor/ithilien/nforest/fpath/fpath2.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("green-shadowed woodlands");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline("You are walking under old trees in ever-green woods. " +
        "The woodlands seem to extend forever in every direction, and " +
        "they are gently falling down towards the west. Above you dark " +
        "leaves form a polished roof in which many birds are singing. " +
        "An ever-present sweet and pungent smell of herbs and flowers " +
        "dominates in Ithilien, the garden of Gondor.");

    add_exit(ITH_DIR + "nforest/fpath/fpath1","east",0,4);
    add_exit(ITH_DIR + "nforest/fpath/fpath3","west",0,4);

    set_up_herbs( ({ HERB_DIR + "athelas", HERB_DIR + "dill",
		     HERB_DIR + "rosemary", }), 
		 ({"ground","field","flowers","forest"}), 3);

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
        "From here the mountains in the east are hidden by many tree tops.\n"));
    add_item( ({"forest","wood","woodlands","herbs","thicket"}),BSN(
        "Many great trees are growing here, cedars and giant oaks and " +
        "hoary ash trees. Many herbs of different forms and scents fill " +
        "the air with sweet and pungent smells."));
}

static string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}
