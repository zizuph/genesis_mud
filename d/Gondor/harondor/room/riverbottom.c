/*
 *	/d/Gondor/harondor/room/riverbottom.c
 *	A room Harondor. This room should not be accessible to mortals. 
 *  October 4, 2004, Serif.
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public void
create_gondor()
{
    set_short("Within the silty waters of a river.");
    set_long("A murky riverbottom in the central parts of the River Poros "
        + "in southern Gondor. It seems to be a little lighter above you "
        + "and a little darker below, but you can not really tell which "
        + "direction is which, since the current constantly turns you "
        + "around. Now and then, a rocky riverbottom wavers in and out of "
        + "sight a few yards away. Silty water flows all around, the fast "
        + "currents pushing against you.\n");
 
    add_item(({"river", "poros", "river poros", "current"}), "The River "
        + "Poros flows all around. The water is silty and difficult "
        + "to see through.\n");
    add_item(({"water", "waters", "flow", "current", "currents"}), 
        "The waters of the River Poros flow all around you on their way "
        + "west toward the sea. The current is turbulent here, turning " 
        + "you around and around.\n");
    add_item(({"surroundings"}), "You are tumbling underwater, caught "
        + "in the currents of a river.\n"); 
    add_item(({"rock", "stone", "rocks", "stones", "silt"}), "Rocks and "
        + "silt fill the riverbed here, shifting with the weight of the "
        + "of the water.\n");
    add_item(({"riverbed", "channel", "river channel"}), "The riverbed "
        + "is just below you, covered with rocks and silt.\n");
    add_item(({"surface", "air", "light"}), "Light and air await at the "
        + "surface of the river, above you somewhere.\n");

    set_no_exit_msg(({"north", "northeast", "east", "southeast",
        "south", "southwest", "west", "northwest"}), "The river currents "
        + "swirl strongly around you, preventing you from swimming "
        + "away.\n");
    set_no_exit_msg(({"down"}), "The riverbed lies in that direction, "
        + "offering no escape.\n");
    set_no_exit_msg(({"up"}), "The currents tumble you away from the surface "
        + "of the river.\n");

    set_drink_from( ({ "river", "poros", "river poros", }) );

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_tell("The river rushes around you.\n");
    add_tell("You tumble in the currents.\n");
    add_tell("Something brushes against you.\n");
    add_tell("Water presses in on you.\n");
    add_tell("The river knocks you against some rocks.\n");
    add_tell("Something quickly floats by but is gone before you can "
        + "examine it closer.\n");
    add_tell("Something seems to swim by you.\n");

    set_tell_time(100);
    reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

void
drink_message(string from)
{
    write("You gulp down some silty water.\n"
        + "Seeing no way out of the currents, you will likely be "
            + "drinking more soon.\n");
    say(QCTNAME(TP) + " gulps down some silty water from the river.\n");
}

void
init()
{
    ::init();
    init_drink();
}
