/*
 *  IGARD_LIB + "outside_funcs.c"
 *
 *  Various functions common to Isengard outside rooms.
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
#include "/d/Gondor/std/tell.c"

/* PROTOTYPES */

public void           add_exterior_tells();
public void           exterior_add_items();


void
add_exterior_tells()
{
    set_tell_time(120);

    add_tell("A wolf howls in the distance.\n");
    add_tell("An eagle cries far overhead.\n");
    add_tell("Harsh voices can be heard on the other side of the ring wall.\n");
    add_tell("You hear shouting atop the ring wall.\n");
    add_tell("Marching feet can be heard somewhere nearby.\n");
    add_tell("Smokes and steams plume into the air beyond the wall.\n");
    add_tell("The ground rumbles beneath your feet.\n");
    add_tell("A gentle breeze flows through the area.\n");
    add_tell("Deep voices grumble in the distance.\n");
    add_tell("Tortured machinery squeals and rattles beyond the ring wall.\n");
}


void
exterior_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"path", "gravel path", "small path"}), "The path beneath "
        + "your feet is made from crushed gravel. It crunches and "
        + "shifts as you walk across it.\n");
    add_item(({"gravel", "crushed gravel"}), "The gravel is made from "
        + "black stone, pulverized many times over in the mines to the "
        + "west, and further ground beneath the heels of many booted feet.\n");
    add_item(({"steam", "smoke", "plume", "plumes", "smokes", "steams"}),
        "The steams and smokes belching from within Isengard look noxious "
        + "and entirely unwholesome.\n");
    add_item(({"wall", "ring wall", "ringed wall"}), "A great wall "
        + "of black stone stands at least one hundred feet tall and "
        + "curves away to the west and east. It appears to be made "
        + "partly from the natural landscape but also by the hand of "
        + "Men. Standing this close to the wall makes it impossible "
        + "to determine how far it extends or what lies on the other "
        + "side. You can, however, see the peaks of the Misty "
        + "Mountains above it.\n");
    add_item(({"landscape", "natural landscape", "terrain"}), "Here at "
        + "the foot of the Misty Mountains, the landscape is partly flat "
        + "but also has many sudden projections of black rock. The wall "
        + "before you is made from a combination of these natural "
        + "outcroppings as well as quarried stone worked by the hands "
        + "of Men.\n");
    add_item(({"rock", "black rock"}), "The great ring wall is made "
        + "from black rock, both natural and that quarried by the hands "
        + "of Men.\n");
     add_item(({"isengard", "fortification"}), "The fortification of "
        + "Isengard stands "
        + "directly in front of you. It can only be entered through "
        + "a gate in the southern section of its ring wall.\n");
}


