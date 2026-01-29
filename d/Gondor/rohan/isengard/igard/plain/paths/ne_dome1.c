/*
 *  IGARD_PLAIN_PATHS + "ne_dome1.c"
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

static object  Troop;
int distance = 3;

public void
create_gondor()
{
    set_short("Before a large dome of stone");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    plain_add_items();
    add_plain_tells();
    path_add_items();
    dome_add_items();

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_item(({"dome", "stone dome", "large stone dome"}), "This large "
        + "structure stands roughly ten feet high and has a circumference "
        + "of approximately forty feet. It is made of the same black stone "
        + "from which the mighty ring wall is constructed and appears "
        + "unbroken save for the great copper pipe rising from its top.\n");
    add_item(({"pipe", "copper pipe", "great copper pipe"}), "The great "
        + "copper pipe rises from the center and top of the dome. It is "
        + "encased in blue deposits from long years of oxidation, but appears "
        + "to be sound. It protrudes several feet above the dome, with great "
        + "gouts of steam and noxious vapours belching from within.\n");

    add_exit(IGARD_PLAIN_PATHS  + "ne_path1e.c", "west");

    add_prop(ROOM_I_INSIDE, 0);

    reset_room();
}


string
long_desc()
{
    return "You stand before a large dome of stone rising upon the "
      + "plain of Isengard like a festering boil." + sky_desc()
      + plain_tower_desc(distance)
      + "Great gouts of steam and unwholesome vapours belch from "
      + "a great copper pipe at its top. Leading away from the dome is "
      + "a small gravel path.\n";
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
     start_room_tells();

}


public void
reset_room()
{
    if (!objectp(Troop))
    {
        Troop = clone_object(IGARD_NPC + "igard_orc4_rider.c");
        Troop->set_restrain_path(IGARD_PLAIN_PATHS);
        Troop->arm_me();
        Troop->move_living("down", TO);
        Troop->add_warg();
        Troop->add_3_orcs(3);
    }
}
