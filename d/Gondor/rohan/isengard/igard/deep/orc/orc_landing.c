/*
 *  IGARD_DEEP_WARG + "orc_landing.c"
 *
 *  Landing at the base of the lift in orc dens.
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
inherit IGARD_LIB + "orcden_funcs.c";
inherit IGARD_LIB + "quest_funcs.c";

#include "/d/Gondor/std/tell.c"

public void        create_gondor();

string
long_desc()
{
    return "You are standing in a large landing carved from the black "
    + "rock beneath the plain of Isengard. The only exit "
    + "appears to be a strange-looking lift to the west.\n";
}


public void
create_gondor()
{
    set_short("A landing before a strange-looking lift");
    set_long(long_desc());

    underground_add_items();

    add_item(({"room", "area", "surroundings", "place", "landing"}), 
        long_desc());

    add_item(({"lift", "strange-looking lift"}), "The lift is made from "
        + "large planes of wood that move up through a wide shaft. What "
        + "mechanism propels it, however, cannot be seen from here.\n");
    add_item(({"planes", "plane", "wood", "planes of wood", "plane of wood"}), 
        "The planes of wood arrive from below and move upward through the "
        + "shaft. They serve as the floor for passengers to stand on while "
        + "riding the lift.\n");
    add_item(({"shaft", "wide shaft"}), "The shaft extends far upward and "
        + "out of sight to the west.\n");

    set_tell_time(120);
    add_tell("The lift clacks loudly.\n");
    add_tell("The lift groans and squeals.\n");
    add_tell("Something clangs and clatters deep within the shaft.\n");
    add_tell("Someone screams high above in the shaft.\n");
    add_tell("The lift grinds to a halt.\n");
    add_tell("The lift lurches suddenly into motions.\n");
    add_tell("You hear a great squealing noise from below.\n");
    add_tell("Clang! It sounds like something in the lift just broke.\n");
    add_tell("Bang! A piece of wooden platform breaks away and tumbles "
        + "down the shaft.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_ORC   + "orc_lift",        "west");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    object orc_clue;

    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();

        if (SOI1)
        {
            TP->remove_prop(SENT_ORCWARG_IGARD1);
            TP->add_prop(FINISHED_ORCWARG_IGARD, 1);
            igard_stage_check();
        }
    }
}