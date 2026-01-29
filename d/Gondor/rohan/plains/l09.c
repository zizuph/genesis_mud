#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

#define RHARD   10

public void
create_plain()
{
    set_geo("flat");
    set_wet("high");
    set_grass("long, dark green");
    set_land("the West Emnet");
    set_where("east");
    set_special(1);
    set_river_name("Deeping Stream");
    set_rhard(RHARD);
    set_rwhere("north");
    add_exit("NotOpen/m09","north", drown, RHARD);
    add_exit("l10","east",      0,     5);
/*
    add_exit("NotOpen/m09","north", crossing, RHARD);
*/
    add_exit("k09","south",     0, 5);
    add_exit("l08","west",      0, 5);

    set_drink_from( ({"stream","river","deeping stream"}) );
}
