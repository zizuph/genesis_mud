/*
 *      /d/Gondor/ithilien/nforest/fpath/fpath7.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      1996, Olorin: Changed inheritance.
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
    set_treetype("oak");
    set_extraline("You are walking under old trees in ever-green woods "
      + "in a shallow cut between hills. The woodlands seem to extend "
      + "forever in every direction, covering the slopes that are "
      + "falling down here towards the west rather steeply. "
      + "An ever-present sweet and pungent smell of herbs and flowers "
      + "dominates in Ithilien, the garden of Gondor.");

    set_up_herbs( ({ HERB_DIR + "tuo", HERB_DIR + "chervil",
                     HERB_DIR + "saffron",
                     ONE_OF_LIST(HERB_MASTER->query_herbs("forest")), }),
        ({ "ground", "field", "flowers", "forest", }), 3);
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item(({"forest","wood","woodlands","herbs","thicket"}), BSN(
        "Many great trees are growing here, cedars and giant oaks "
      + "and hoary ash trees. Many herbs of different forms and scents "
      + "fill the air with sweet and pungent smells. The land is "
      + "falling down steeply towards the great vales of the Anduin."));
    add_item(({"slope", "slopes", "land", }), BSN(
        "The hill country of the east has come to an end here. In a "
      + "long edge it falls down to the great vales on the bank of the "
      + "Anduin, sometimes in long hillsides, like here, sometimes "
      + "suddenly and sheer, like further south."));
    add_exit(ITH_DIR + "nforest/fpath/fpath6", "northeast", 0, 5);
    add_exit(ITH_DIR + "nforest/fpath/fpath8", "southwest", 0, 5);
}

string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

