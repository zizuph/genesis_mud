/*
 *  /d/Sparkle/area/orc_temple/rooms/3_hall8.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 3.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "pentagram_room";


/* Prototypes */
public void         create_pentagram_room();


/*
 * Function name:        create_pentagram_room
 * Description  :        constructor for the room
 */
public void
create_pentagram_room()
{
    set_side("southeast");
    set_extraline("A narrow tunnel leads south into distant gloom.");

    add_item( ({ "southeastern end", "end" }),
        "Here, you stand at one point of a colossal pentagram that"
      + " is constructed of candles.\n");
    add_item( ({ "tunnel", "narrow tunnel", "south" }),
        "A narrow tunnel is leading out of the chamber to the south."
      + " I very intense sense of unease grips you as you peer down"
      + " its length.\n");
    add_item( ({ "unease", "sense", "sense of unease" }),
        "There is something that way ... something ... horrifying.\n");
    add_item( ({ "something", "horrifying", "something horrifying" }),
        "Thinking more about it begins to tear at your sanity.\n");
    add_item( ({ "sanity" }),
        "Stop! It ... must ... stop ...\n");

    add_exit("3_pit", "northwest", check_exit, 1, 0);
    add_exit("3_hall7", "north");
    add_exit("3_hall1", "west");
    add_exit("3_hall9", "south");

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_pentagram_room */
