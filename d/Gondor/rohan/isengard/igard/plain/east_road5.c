/*
 *  IGARD_PLAIN + "east_road5.c"
 *
 *  Eastern road on the plain of Isengard.
 *
 *  Last modified by Alto, 19 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "plain_funcs.c";

public void        create_gondor();
public string      long_desc();

int distance = 4;

public void
create_gondor()
{
    set_short("A street on the eastern plain of Isengard");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    plain_add_items();
    add_plain_tells();

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_item(({"street", "wide street", "road"}), "A wide street leads west "
        + "from the ring wall. It is paved with stone-flags, dark and hard, "
        + "squared and laid with great skill. No blade of grass can "
        + "be seen in any joint. Long lines of pillars, some of marble, "
        + "some of copper and of iron march along the road in long lines.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(IGARD_PLAIN  + "east_road4.c",      "east");
    add_exit(IGARD_PLAIN  + "east_road6.c",      "west");

    reset_room();
}


string
long_desc()
{
    return "You are standing on a street built with great skill on the "
      + "eastern plain of Isengard." + sky_desc() + plain_tower_desc(distance)
      + "\n";
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
     start_room_tells();

}

