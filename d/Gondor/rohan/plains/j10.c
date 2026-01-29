/*
 *	/d/Gondor/rohan/plains/j10.c
 *
 *	Coded by Olorin.
 *
 */
#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain";

#include <macros.h>

#include "/d/Gondor/defs.h"

#define RHARD		10

public void
create_plain()
{
    set_geo("flat");
    set_wet("high");
    set_grass("thick, dark green");
    set_land("the Westfold");
    set_where("northeast");
    set_special(1);
    set_river_name("Entwash");
    set_rhard(RHARD);
    set_rwhere("east");
    add_exit("k10", "north",     0,     5);
    add_exit("NotOpen/j11", "east",  drown, RHARD);
/*
    add_exit(ENTWASH_DIR + "str2", "east", crossing);
*/
    add_exit("i10", "south",     0,     5);
    add_exit("j09", "west",      0,     5);

    set_drink_from( ({"entwash","river","stream"}) );
    
    set_npc_file(ROH_DIR + "npc/westfoldorc");
    set_npc_number(1);

    reset_room();
}
