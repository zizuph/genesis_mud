/*
 *  IGARD_PLAIN + "south_gate.c"
 *
 *  Great southern gate of Isengard.
 *
 *  Last modified by Alto, 23 September 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "gate_funcs.c";

public void        create_gondor();
public int         permit_entry();
public string      long_desc();

public void
create_gondor()
{
    set_short("The great southern gate of Isengard");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    plain_add_items();
    gate_add_items();

    add_item(({"inscription", "weathered inscription"}), &exa_inscription());
    add_cmd_item(({"inscription", "weathered inscription"}), "read",
        &exa_inscription());

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_item(({"street", "wide street", "road"}), "A wide street leads north "
        + "from the ring wall. It is paved with stone-flags, dark and hard, "
        + "squared and laid with great skill. No blade of grass can "
        + "be seen in any joint. Long lines of pillars, some of marble, "
        + "some of copper and of iron march along the road in long lines.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(IGARD_PLAIN  + "south_road1.c",      "north");

    reset_room();
}


string
long_desc()
{
    return "Two mighty doors of iron rise above you here at the "
      + "southern end of the great plain of Isengard. The doors are set "
      + "beneath an arch in the great ringed wall of black sheer rock that "
      + "reaches toward the sky like a towering cliff." + sky_desc() 
      + " The vast immensity of this place, a natural wonder yet hewn by "
      + "the hands of men, humbles even the proudest soul to pass her "
      + "gates. There is a weathered inscription carved into the black stone "
      + "of the arch. A street leads north onto the great encircled plain and "
      + "eventually down to the mighty tower lurking in its center.\n";
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
}


int
permit_entry()
{
    actor = TP;

    write("You push on the massive iron doors with both hands. Much to "
        + "your surprise, they swing easily upon their hinges. You "
        + "quickly slip inside as the doors close behind you.\n\n");
    tell_room(environment(actor), QCTNAME(actor) + " pushes on the massive "
        + "iron doors with both hands. The doors open effortlessly and "
        +  PRONOUN(actor) + " slips quietly inside.\n"
        + "The doors return to their original position.\n", 
        ({actor}));
    tell_room(IGARD_WALL + "gate_tun6", QCPNAME(TP) + " footsteps "
        + "echo across the tunnel as " + PRONOUN(actor) + " enters "
        + "through the massive iron doors.\n"
        + "The doors return to their original position.\n");

    TP->move_living("M", IGARD_WALL + "gate_tun6", 1, 0);

    return 1;
}


