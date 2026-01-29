/*
 *      /d/Gondor/rohan/road/er2.c
 *
 *      Copyright (c) 1997 by Christian Markus
 *
 *      Modification log:
 *      26-Jan-1997, Olorin:    Changed inheritance,
 *                              general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

public void
create_roads() 
{
    set_street("dusty, stonelaid road");
    set_where("south");
    set_county("Eastfold");
    set_land("Rohan");
    set_mountain("White Mountains");
    set_vegetation("long, dark green grass");
    set_extraline("Far to the north, the silvery band of a river can be "
        + "seen running through the dark green grass of the plains of "
        + "Rohan. To the south, the White Mountains with their snow-covered "
        + "peaks are rising beyond green valleys and forests. The Great "
        + "West Road continues northwest and south.");

    add_exit(ROH_DIR + "plains/g10", "north",     0, 3);
    add_exit(ROH_DIR + "plains/f11", "east",      0, 3);
    add_exit(ROH_DIR + "road/er3",   "south",     0, 2);
    add_exit(ROH_DIR + "road/er1",   "northwest", 0, 2);

    add_item( ({ "river", "band", "snowbourn", }), BSN("The river "
        + "in the north must be the Snowbourn on its way to the "
        + "Anduin in the east."));
    add_item( ({ "mountains", "white mountains", "peaks", }), BSN(
        "The White Moutains and their snow-covered peaks run like an "
            + "unbroken wall far to the west and east. Beneath the "
            + "peaks, many valleys are opening between green "
            + "hills."));
    add_item( ({ "hills", "forests", "valleys", }), BSN("At the "
        + "feet of the mountains, many green valleys open between "
        + "hills that are covered by dense forests."));
}

