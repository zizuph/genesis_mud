/*
 * h_master.c
 *
 * Harbour master's office of Port MacDunn.
 *
 * Khail - March 30/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

object master;

public int *
query_local_coords()
{
    return ({10,8});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public void
reset_room()
{
    if (!master)
    {
        reset_euid();
        master = clone_object(NPC + "wullie");
        master->arm_me();
        master->move(TO);
        tell_room(TO, QCTNAME(TO) + " steps inside from " +
            "the street.\n");
        return;
    }

    else if (!present(master, TO))
    {
        if (master->query_attack())
            return;
        master->command("emote looks around suddenly, and seems " +
            "to decide it's time to be elsewhere.");
        master->move_living("M", TO);
        master->command("emote arrives from the street outside.");
    }
}
    
public int
get_leaflet (string str)
{
    object leaflet;

    if (objectp(leaflet = clone_object("/d/Sparkle/area/city/shiplines/office/leaflet")))
    {
        leaflet->move(TP);
        write("You pick a leaflet from the heap on the desk.\n");
        tell_room(QCTNAME(TP) + " picks up a leaflet from the heap "
            + "next to the desk.\n");
    }

    return 1;
}

/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
  object timetable;
    set_short("Harbour Master's Office of Port MacDunn");
    set_long("   You've entered a small stone building that has " +
        "been decorated to look much like the captain's " +
        "room on a sea-going ship, even to the point of " +
        "using wood panels on the wall and planking on the " +
        "floor. A table in the middle of the room is loaded " +
        "with a variety of charts, maps, and nautical " +
        "navigation equipment. Towards the back of the room, " +
        "a low desk scattered with papers is backed by a " +
        "large painting of a stormy ocean.\n");

    add_item(({"floor", "ground", "planking"}),
        "The floor of the office has been covered with " +
        "wooden planking.\n");
    add_item(({"walls", "wall"}),
        "The walls are stone, judging from the exterior of the " +
        "building, but have been covered on the inside with " +
        "wood panels.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the office is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"thatch", "seaweed", "seagrass"}),
        "The thatch looks to be tightly-bundled mats of " +
        "some sort of seagrass or seaweed.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "very thin wooden rafters.\n");
    add_item(({"painting"}),
        "The painting on the wall is fairly simple, merely " +
        "white-caps on dark water, as if the image depicts a " +
        "mild storm.\n");
    add_item(({"desk"}),
        "The desk has been made from wood, and is moderately " +
        "water stained, as if salvaged from a wreck. The desk "+
             "contains several small leaflets you can get.\n");
    add_cmd_item(({"leaflet", "leaflets"}),
                 ({"get", "take", "pick", "grab" }),
                 get_leaflet,
                 );
    add_item(({"papers"}),
        "You glance at the papers lying on the desk, but nothing " +
        "seems very interesting.\n");
    add_item(({"table"}),
        "The table in the middle of the room is actually quite " +
        "crude, but strong enough to hold a large assortment of " +
        "odds and ends.\n");
    add_item(({"maps", "charts", "map", "chart"}),
        "The maps and charts all depict various coastal regions " +
        "and navigational channels, but nothing very interesting.\n");
    add_item(({"equipment", "navigation equipment", 
        "nautical navigation equipment"}),
        "Most of the equipment is unknown to you, though you " +
        "recognize a compass and sextant in the assortment.\n");
    add_item(({"compass"}),
        "A simple little device, containing a needle which " +
        "always points towards the north.\n");
    add_item(({"sextant"}),
        "This device is a rather curious combination of mirrors, " +
        "lenses and metal bars. Supposedly it'll help tell you " +
        "where you are, but you've no idea how.\n");
    timetable = clone_object("/d/Khalakhor/inisi/roke/nyreese/gs_office/timetable");
    timetable->set_timetable_domain("Port Macdunn");
    timetable->move(TO);
    timetable->set_no_show_composite(0);

    INSIDE;

    add_exit(ROOM + "road_10_9", "south");

    reset_room();
}

