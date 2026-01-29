/*
 *      /d/Gondor/rohan/road/er5.c
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
    set_street("big, well travelled, dirty turnpike");
    set_where("northwest");
    set_county("Fenmark");
    set_land("Rohan");
    set_mountain("Ered Nimrais");
    set_vegetation("green long grass");
    set_extraline("In all direction save to the south, green long "
        + "grass covers the land. To the south rise green hills and "
        + "beyind them the steep slopes of the White Mountains. The "
        + "road continues to the southeast and the northwest.");

    add_exit(ROH_DIR + "plains/d12", "north",     0, 3);
    add_exit(ROH_DIR + "plains/c13", "east",      0, 3);
    add_exit(ROH_DIR + "road/er6",   "southeast", 0, 2);
    add_exit(ROH_DIR + "road/er4",   "northwest", 0, 2);

    add_item( ({ "mountains", "white mountains", "slopes", }), BSN(
        "South of the road, the northernmost slopes of the White "
            + "Mountains are gradually rising towards the "
            + "snow-covered peaks of the mountain-range that command "
            + "the southern horizon. Between the slopes, wide green "
            + "valleys are opening."));
    add_item( ({ "hills", "valleys", }), BSN("The slopes of the "
        + "mountains from hills that are covered by green forests. "
        + "Between them lie wide valleys where green grass is "
        + "growing."));

    reset_room();
}

public void
reset_room()
{
    if (!objectp(present("helmet")))
        clone_object(ARM_DIR + "fhelmet")->move(TO);
}

