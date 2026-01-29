/*
 *  IGARD_DEEP_WARG + "warg_den4.c"
 *
 *  Warg dens below Isengard.
 *
 *  Last modified by Alto, 24 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "warg_funcs.c";

public void        create_gondor();


public void
create_gondor()
{
    warg_extraline();

    set_short("A shallow den");
    set_long(warg_long_desc());

    underground_add_items();
    warg_add_items();

    add_item(({"room", "area", "surroundings", "place", "passage", "den"}), 
        warg_long_desc());

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_WARG + "warg_den5",         "southwest");
    add_exit(IGARD_DEEP_WARG + "warg_den3",         "northeast");

    reset_room();
}


void
reset_room()
{
    add_wargs_to_room();
}


public void
init()
{
    ::init();
    init_drink();
}
