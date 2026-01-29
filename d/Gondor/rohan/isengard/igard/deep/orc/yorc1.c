/*
 *  IGARD_DEEP_ORC + "yorc1.c"
 *
 *  Orc dens below Isengard.
 *
 *  Last modified by Alto, 25 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "orcden_funcs.c";

public void        create_gondor();


public void
create_gondor()
{
    orcden_extraline();

    set_short("A dank and humid room");
    set_long(orcden_long_desc());

    underground_add_items();
    orcden_add_items();

    add_item(({"room", "area", "surroundings", "place", "passage", "den"}), 
        orcden_long_desc());

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_ORC + "yorc2", "south", check_monster, 2, 0);

    reset_room();
}


void
reset_room()
{
    add_youngorcs_to_room();
}

