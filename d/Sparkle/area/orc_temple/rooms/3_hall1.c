/*
 *  /d/Sparkle/area/orc_temple/rooms/3_hall1.c
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
    set_side("south");
    set_extraline("A short passage travels south.");

    add_item( ({ "stair", "stairs", "step", "steps",
                 "dark step", "dark steps", "dark stone step",
                 "dark stone steps", "stairway", "stone stair",
                 "stone step", "stone stairs", "stone steps",
                 "dark stairs", "dark stair",
                 "dark stairway" }),
        "The stairs are only barely visible from here. You'd need"
      + " to head south to see them clearly.\n");
    add_item( ({ "short passage", "passage", }),
        "It leads south toward what appear to be dark stone steps.\n");
    add_item( ({ "southern end", "end" }),
        "Here, you stand between two points of a colossal pentagram that"
      + " is constructed of candles.\n");

    add_exit("3_pit", "north", check_exit, 1, 0);
    add_exit("3_hall7", "northeast");
    add_exit("3_hall8", "east");
    add_exit("3_up", "south");
    add_exit("3_hall2", "west");
    add_exit("3_hall3", "northwest");

    set_no_exit_msg( ({ "southeast", "southwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_pentagram_room */
