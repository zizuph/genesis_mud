/*
 *  IGARD_PLAIN + "isle2.c"
 *
 *  Isle of rock at the base of Orthanc.
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

public void
create_gondor()
{
    set_short("On the isle of rock at the foot of Orthanc");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    plain_add_items();
    isle_add_items();

    add_item(({"room", "area", "surroundings", "isle", "place",
        "landscape"}), long_desc);

    add_item(({"street", "wide street", "road"}), "A wide street leads away "
        + "from Orthanc toward the ring wall. It is paved with stone-flags, "
        + "dark and hard, squared and laid with great skill. No blade of grass "
        + "can be seen in any joint. Long lines of pillars, some of marble, "
        + "some of copper and of iron march along the road in long lines.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(IGARD_PLAIN  + "north_road10",     "north");
    add_exit(IGARD_PLAIN  + "isle1",            "east");
    add_exit(IGARD_PLAIN  + "isle3",            "west");

    reset_room();
}


string
long_desc()
{
    return "You stand at the very foot of the mighty tower Orthanc, which "
      + "vaults high into the sky over your head. The isle of rock at its "
      + "base is black and gleams as if it is wet. The many faces of the "
      + "stone have sharp edges as though they have been newly chiselled." 
      + sky_desc() + " A street leads to the north, and a small path leads "
      + "around the isle to the east and west.\n";
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
}

