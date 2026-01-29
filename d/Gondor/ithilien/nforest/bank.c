/*
 *      /d/Gondor/ithilien/nforest/bank.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      31-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public int     cross_stream();

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("long bank");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress");
    set_extraline("North of the bank, a small lake lies in a shallow " +
        "dell. The outlet of the lake feeds a small stream that runs " +
        "westward at the foot of the bank. At the top of the bank, " +
        "you can see green-shadowed woodlands with large cedars, oaks, " +
        "and ash trees. An ever-present sweet and pungent smell of " +
        "herbs and flowers dominates in Ithilien, the garden of Gondor.");

    set_up_herbs( ({ HERB_DIR + "garlic",  HERB_DIR + "ginger", 
		     HERB_DIR + "hemlock", HERB_DIR + "mint", 
		     HERB_DIR + "suranie", HERB_DIR + "rosemary" }), 
		  ({ "forest", "ground", "field", "flowers", }), 3);
    add_item( ({"mountains","mountain-range","mountain","ephel duath"}), 
        BSN("From here the mountains named Ephel Duath appear as dark " +
        "grey shadows beyond the stony ridge to the east. You judge " +
        "the mountains to be between 5000 to 7000 feet tall, and you " +
        "guess they are several miles away now."));
    add_item( ({ "forest", "wood", "woods", "herbs", "groves", "thickets",
		 "thicket", "grove", }), BSN(
        "Many great trees are growing here, planted long ago, falling " +
        "into untended age amid a riot of careless descendants. There " +
        "are cedars and giant oaks and hoary ash trees. Many herbs of " +
        "different forms and scents fill the air with sweet and pungent " +
        "smells."));
    add_item( ({ "stream", }), 
        "The stream spills out over a stony lip at the southwest end " +
        "of the lake.\n");
    add_item( ({ "lake", "basin", "pool"," water", }), BSN(
        "The lake is in the broken ruins of an ancient stone basin in " +
        "the dell. Mosses and brambles cover the carven rim, and " +
        "water-lilies are floating on the gently-rippling water. The " +
        "water is constantly renewed by the stream flowing into it " +
        "from the east, while it spills softly out over a stony lip " +
        "at the southwest end."));

    add_exit(ITH_DIR + "nforest/outfall",      "north",     cross_stream, 2);
    add_exit(ITH_DIR + "nforest/bank2",        "east",      0, 1);
    add_exit(ITH_DIR + "nforest/fpath/fpath1", "southwest", 0, 1);

    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    set_drink_from( ({ "lake", "pool", "stream", }) );
}

public int
cross_stream()
{
    write("You cross the small stream.\n");
    return 0;
}

public void
init()
{
    ::init();

    init_drink();
}
