/*
 *	/d/Gondor/harondor/room/road01.c
 *
 *	A room on the Harad Road in Ithilien.
 *
 *  October 9, 2004, Serif.
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

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
        + "the River Poros lie to the south. Across the river, over the "
        + "bridge, the Harad Road resumes on its way through Harondor.");

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

    add_exit("/d/Gondor/ithilien/poros/ford_north", "north");
    add_exit(HAR_RM_DIR + "bridge01", "south");

    set_no_exit_msg(({"west"}), "You try to push through the dense "
        + "willows, but they are too thick here.\n");
    set_no_exit_msg(({"northeast", "northwest"}), "You wander around "
        + "near the road for a while.\n");
    set_no_exit_msg(({"southeast"}), "You wander around the scrublands "
        + "for a while.\n");
    set_no_exit_msg(({"southwest", "southeast"}), "It is too "
        + "difficult to cross the river anywhere but through the "
        + "fords directly south of here.\n");
    set_no_exit_msg(({"east"}), "You start to walk east, but you "
        + "stop at a steep hillside.\n");

    add_cmd_item(({"river", "the river", "ford", "the ford", "poros",
        "river poros", "the river poros", "south"}), ({"swim", "cross",
        "ford", "wade"}), "@@ford_river");

}

mixed
ford_river()
{
    if (TP->query_prop(LIVE_O_STEED) != 0) /*On a steed, can't cross.*/
    {
	write("It is unsafe to lead your steed into the treacherous ford!\n");
	say(QCTNAME(this_player())+" tries cross the ford while mounted, "
        + "but "+this_player()->query_possessive()+" steed shies "
        + "away from the river.\n",this_player());
        return 1;
    }
    if (TP->query_prop(LIVE_O_STEED) == 0) /*No steed, ok to cross.*/
    {
    if (TP->query_skill(SS_SWIM) > 20+random(10)) /*Swims well, can cross.*/
        {
    write("You manage to wade through the swift currents and ford the river "
        + "partway.\n");
        say(QCTNAME(TP)+" leaves fording the river.\n");
        TP->move_living("M", "/d/Gondor/harondor/room/ford01", 1);
        say(QCNAME(TP) + " arrives wading through the river from "
           + "the north.\n");
       return 1;  /*Player is moved across the river.*/
        }
    else  /*Can't swim well, can't cross.*/
    write("You struggle to cross the river, but you cannot keep your "
      + "footing while you fight against the current.\n");
    say(QCTNAME(TP)+" tries to ford the river, but fails.\n");
    return 1;
    }
    return 1;
}

public void
drink_message(string from)
{
    write("You climb down closer to the river beside the bridge and drink " +
          "some silty water from the River Poros.\n" +
          "It tastes a little bitter, but you feel refreshed.\n");
    say(QCTNAME(TP) + " climbs down closer to the river beside the bridge " +
          "and drinks some silty water from the river.\n");
}

public void
init()
{
    ::init();
    init_drink();
}
