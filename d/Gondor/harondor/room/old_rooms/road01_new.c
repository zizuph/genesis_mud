/*
 *	/d/Gondor/harondor/room/road01.c
 *
 *	A room on the Harad Road in Ithilien.
 *
 *  October 9, 2004, Serif.
 * 
 * Modified room to have a bridge over the river Poros so the armies 
 * of Harad can march up it towards Mordor.
 * -- Finwe, July 2005
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";
//inherit "/w/serif/harondor/lib/block_steed.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("plain");
    set_grass("short, thin");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs north through Ithilien, east of the "
        + "slopes of the Ephel Duath. Next to a steep hill, the fords of "
        + "the River Poros lie to the south. Across the river, the Harad "
        + "Road resumes its way through Harondor.");
 
    add_item(({"road", "harad road"}), "The ancient trade road "
        + "between Gondor and Harad, the Harad Road, crosses "
        + "the River Poros here.\n");
    add_item(({"river", "poros", "river poros", "current"}), "The river "
        + "interrupts the road here as it flows swiftly toward the "
        + "west. It is shallow enough to cross here most times of "
        + "the year. However, the current is still swift.\n");
    add_item(({"ford", "fords"}), "The river widens out here, "
        + "its flow swift but shallow. It is possible to travel "
        + "south across the ford.\n");
    add_item(({"plain", "plains"}), "A small grassy plain "
        + "extends along the road here.\n");
    add_item(({"mountain", "mountains", "ephel duath", "peak",
        "peaks", "slope", "slopes"}), "The peaks of the Ephel Duath "
        + "loom ominously in the east.\n");
    add_item(({"hill", "hillside", "steep hill", "steep hillside"}), 
        "A hillside leads steeply up on the eastern side of the road.\n");

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    set_drink_from( ({ "river", "poros", "river poros", "River Poros", 
        "Poros", "water", "the river", "the river poros", "the Poros",
        "the River Poros" }) );

    add_exit(POROS_DIR +  "ford_north", "north");
    add_exit(HAR_RM_DIR + "road02", "south", "@@block_room@@", 0);



    set_no_exit_msg(({"west"}), "You try to push through the dense "
        + "willows, but they are too thick here.\n");
    set_no_exit_msg(({"northeast", "northwest"}), "You wander around "
        + "near the road for a while.\n");
    set_no_exit_msg(({"southeast"}), "You wander around the scrublands "
        + "for a while.\n");
    set_no_exit_msg(({"southwest", "southeast"}), "It is too "
        + "difficult to cross the river anywhere but through the "
        + "fords directly south of here.\n");
    set_no_exit_msg(({"south"}), "You start to wade into the river, "
        + "but you realize that you cannot simply walk across.\n");
    set_no_exit_msg(({"east"}), "You start to walk east, but you "
        + "stop at a steep hillside.\n");
}
int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You cannot go there yet.\n");
    return 1;
}

public void
drink_message(string from)
{
    write("You drink some silty water from the River Poros.\n"
        + "It tastes a little bitter, but you feel refreshed.\n");
    say(QCTNAME(TP) + " drinks some silty water from the river.\n");
}

public void
init()
{
    ::init();
    init_drink();
}
