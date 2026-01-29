/*
 *  /d/Sparkle/area/city/rooms/streets/center_c.c
 *
 *  This is the point at which the road through the Old City Gate
 *  enters the Old City.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 *  Updated by Gronkas August 4, 2016 to fix a typo
 *
 */
#pragma strict_types

#include "../../defs.h"
inherit ROOMS_DIR + "outdoor_room";


/* Prototpyes */
public void        create_sparkle();


/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    set_quadrant("center");
    set_street(STREET_CENTER);

    set_short_extra("West, the city gate leads out of the center of"
      + " town");
    set_long_extra("The old city gate yawns over the street which"
      + " passes through it on its way out of this old section of town"
      + " to the west, where an old humpbacked bridge is visible in"
      + " the far distance. Construction is evident on both sides of"
      + " the western road, where new buildings are being constructed"
      + " before the old walls of the city.");

    try_item( ({ "gate", "city gate", "old gate", "gates", "city gates",
                 "old gates", "old city gate", "old city gates",
                 "gates of the city", "gates of the old city" }),
        "The old city gate was once the only entrance into Sparkle"
      + " other than by ship. As time has passed, the city has come"
      + " to grow beyond the old wall and thus, a new wall has"
      + " been constructed to surround what the city has become."
      + " Though no longer considered a primary defence, the gate"
      + " is extremely imposing, and opens to the west where it"
      + " covers the street which passes through it on the way out"
      + " of town.\n");
    try_item( ({ "entrance", "entrance to sparkle" }),
        "The old city gate is no longer the only entrance to the"
      + " city, but it remains a reminder of times gone by.\n");
    try_item( ({ "new wall", "newer wall" }),
        "It is not visible from here in the center of town.\n");
    try_item( ({ "bridge", "humpbacked bridge", "old bridge",
                 "old humpbacked bridge" }),
        "It is a great distance to the west. You'd have to head that"
      + " direction to see any detail.\n");
    try_item( ({ "new building", "new buildings" }),
        "Hard to tell what will eventually be here. There is a great"
      + " deal of hard work taking place to bring the city in line"
      + " with recent demands.\n");

    add_cmd_item( ({ "gate", "city gate", "old city gate",
                     "gates", "city gates", "old city gates",
                     "gates of the city" }),
                  ({ "enter" }),
        "To do that, you'd just need to travel west.\n");

    add_center_items();

    add_tell("A wagon carrying goods passes through the gate into the"
      + " city and turns south heading toward the docks.\n");
    add_tell("A few guards move back and forth atop the old city"
      + " wall, looking down over both sides of the gate.\n");
    add_tell("Someone bumps you heading north, carrying a large"
      + " stack of what appear to be sealed envelopes.\n");
    add_tell("The sun dims briefly as a cloud passes before it.\n");
    add_tell("The chirping of birds echoes from behind nearby"
      + " rooftops.\n");

    add_exit("center_b", "north");
    add_exit("center_d", "south");
    add_exit("/d/Genesis/start/human/town/vill_gate", "west");
//  add_exit("west_a", "west");
} /* create_sparkle */
