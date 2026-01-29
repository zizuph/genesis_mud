/*
 *  /d/Sparkle/area/orc_temple/rooms/3_hall3.c
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
    set_side("west");
    set_extraline("A table rests against the wall here.");

    add_item( ({ "table" }),
        "The table is made of black stone, and holds various arcane"
      + " objects.\n");
    add_item( ({ "stone", "black stone" }),
        "The black stone is roughly hewn, but also carved with some"
      + " fairly delicate symbols.\n");
    add_item( ({ "symbols" }),
        "The symbols are not ones you recognize, but they have an"
      + " unmistakably ominous quality.\n");
    add_item( ({ "objects", "arcane objects", "arcane object" }),
        "The objects look ritualistic in nature, not having any clear"
      + " purpose as tools or weapons.\n");
    add_item( ({ "western end", "end" }),
        "Here, you stand at the point of a colossal pentagram that"
      + " is constructed of candles.\n");
    add_item( ({ "magic barrier", "barrier", "magic",
                 "powerful magic", "powerful barrier",
                 "powerful magic barrier" }),
        "It is invisible. Dang.\n");

    add_cmd_item( ({ "object", "objects", "arcane objects",
                     "arcane object", "table" }),
                  ({ "get", "take", "steal", "move", "search" }),
        "There is a powerful magic barrier that prevents you from"
      + " approaching the table.\n");

    add_exit("3_hall4", "north");
    add_exit("3_hall5", "northeast");
    add_exit("3_pit", "east", check_exit, 1, 0);
    add_exit("3_hall1", "southeast");
    add_exit("3_hall2", "south");

    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_pentagram_room */
