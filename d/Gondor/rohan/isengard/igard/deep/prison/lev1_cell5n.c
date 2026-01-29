/*
 *  IGARD_DEEP_PRISON + "lev1_cell5n.c"
 *
 *  Prison cell in the prisons below Isengard.
 *
 *  Last modified by Alto, 13 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "prison_funcs.c";

public void        create_gondor();


public void
create_gondor()
{
    cell_extraline();

    set_short("A small cramped prison cell");
    set_long(cell_long_desc());

    prison_add_items();
    cell_add_items();

    add_item(({"room", "area", "surroundings", "place", "passage", "cell"}), 
        cell_long_desc());

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_PRISON + "lev1_hall5",          "south");

    reset_room();
}


void
reset_room()
{
    add_human_prisoners();
}