/*
 *      /d/Gondor/ithilien/nforest/bank1.c
 *
 *      Coded 1993 by Olorin 
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance to area_room.
 *      04-Okt-2008, Eowul:    Added drinking support 
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Rabbit = allocate(2 + random(3));

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("small lake");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress");
    set_extraline("You are standing at the western end of the clear lake. It "+
        "lies in the broken ruins of an ancient stone basin, the carven rim of "+
        "which is almost wholly covered with mosses and rose-brambles. "+
        "Not far from here, the water spills ever softly over a stony lip into a small stream. "+
        "Thickets of cypresses and "+
        "dark-leaved bay-trees grow upon the steep banks above the lake.");

    add_exit(ITH_DIR + "nforest/slope3",  "north",     0, 1);
    add_exit(ITH_DIR + "nforest/lake",    "northeast", 0, 1);
    add_exit(ITH_DIR + "nforest/outfall", "south",     0, 1);
    add_exit(ITH_DIR + "nforest/slope4",  "west",      0, 1);

    set_up_herbs( ({ HERB_DIR+"ungolestel", HERB_DIR+"tyelka",
                         HERB_DIR+"tuo", HERB_DIR+"tarragon",
                         HERB_DIR+"saffron", HERB_DIR+"laurel", }),
        ({"forest","ground","field","flowers","forest"}), 3);

    add_item("rim", BSN("The rim is skillfully built up of carved "
        + "stones, many long years ago. Some stones have been "
        + "displaced with the years, and the basin looks disused."));
    add_item( ({"mountains", "mountain-range", "mountain", 
                    "ephel duath"}), 
        BSN("From here the mountains named Ephel Duath appear as dark "
            + "grey shadows beyond the stony ridge to the east. You "
            + "judge the mountains to be between 5000 to 7000 feet "
            + "tall, and you guess they are several miles away now."));
    add_item(({"forest","wood","woods","herbs","thickets","thicket"}),
        BSN("Many great trees are growing here, planted long ago, "
            + "falling into untended age amid a riot of careless "
            + "descendants. There are olive and bay, cedars high on "
            + "the top of the banks surrounding the dell, and many "
            + "other herbs of different forms and scents."));
    add_item(({"flower", "flowers", "water-lily", "iris", "lily",
                   "iris-swords"}), 
        BSN("Iris-swords are standing in ranks about the basin's rim, "
            + "and water-lily leaves are floating on the dark "
            + "gently-rippling surface of the water."));
    add_item( ({"stream"}), BSN("The lake is fed by a stream running "
        + "down the ridge hidden by the forest to the east, while the "
        + "stream spills out over a stony lip at the southwest end of "
        + "the lake not far from here."));
    add_item(({"lake","basin","pool","water"}), BSN("The lake is in "
        + "the broken ruins of an ancient stone basin in the "
        + "dell. Mosses and brambles cover the carven rim, and "
        + "water-lilies are floating on the gently-rippling water. "
        + "The water is constantly renewed by the stream flowing into "
        + "it from the east, while it spills softly out over a stony "
        + "lip at the southwest end, not far from here."));

    set_drink_from( ({ "lake", "basin", "pool", }) );
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Rabbit, NPC_DIR + "rabbit", 20.0 + 20.0 * rnd());
}

public void
init()
{
    ::init();

    init_drink();
}