/*
 *  IGARD_PLAIN_PATHS + "ne_path2c.c"
 *
 *  Experimental path on the plain of Isengard.
 *
 *  Last modified by Alto, 22 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "plain_funcs.c";

public void        create_gondor();
public string      long_desc();

int distance = 5;

public void
create_gondor()
{
    set_short("A gravel path on the plain of Isengard");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    plain_add_items();
    add_plain_tells();
    path_add_items();

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_exit(IGARD_PLAIN_PATHS  + "ne_path2b.c",          "south");
    add_exit(IGARD_PLAIN_PATHS  + "ne_path2d.c",          "north");

    add_prop(ROOM_I_INSIDE, 0);

    reset_room();
}


string
long_desc()
{
    return "This is a small gravel path on the northeastern plain of "
      + "Isengard." + sky_desc() + plain_tower_desc(distance)
      + "Near at hand, the plain is broken by numerous shafts covered "
      + "with low mounds and domes of stone.\n";
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
     start_room_tells();

}

