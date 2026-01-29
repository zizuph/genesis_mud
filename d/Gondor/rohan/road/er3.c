/*
 *      /d/Gondor/rohan/road/er3.c
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

public void    reset_room();

public void
create_roads() 
{
    set_street("big, newly used turnpike");
    set_where("south");
    set_county("Eastfold");
    set_land("Rohan");
    set_mountain("Ered Nimrais");
    set_vegetation("green long grass");
    set_extraline("The sound of running water can be heard from the north, "
        + "where the river Snowbourn is running towards to Anduin in the "
        + "east. In all direction, green long grass covers the land of "
        + "the Eastfold. To the south, the White Mountains are rising under "
        + "their snow-covered peaks. The road continues north and southeast.");

    add_exit(ROH_DIR + "road/er2",   "north",     0, 2);
    add_exit(ROH_DIR + "plains/e11", "east",      0, 3);
    add_exit(ROH_DIR + "road/er4",   "southeast", 0, 2);

    reset_room();
}

public void
reset_room()
{
    if (!objectp(present("trousers", TO)))
        clone_object(ARM_DIR + "ltrousers")->move(TO);
}
