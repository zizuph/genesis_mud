/*
 *  /d/Sparkle/area/orc_temple/rooms/3_hall5.c
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
    set_side("north");
    set_extraline("A low altar has been placed along the wall.");


    add_item( ({ "northern end", "end" }),
        "Here, you stand at one point of a colossal pentagram that"
      + " is constructed of candles.\n");
    add_item( ({ "altar", "low altar" }),
        "The altar is completely bare except for a strange symbol"
      + " that has been painted along its surface.\n");
    add_item( ({ "symbol", "strange symbol" }),
        "The symbol looks almost like a primitive pictogram.\n");
    add_item( ({ "pictogram", "primitive pictogram" }),
        "The pictogram depicts a great amorphous thing with many"
      + " eyes. Looking at it sends chills down your entire body.\n");
    add_item( ({ "amorphous thing", "thing", "eyes", "many eyes", }),
        "@@yogsothoth@@");

    add_delay_cmd_item(
        ({ "altar", "low altar", }),
        "search",
        "searching the altar",
        10,
        "You begin searching the altar.\n",
        "Carved beneath a pictogram on the altar, you discover very"
      + " small letters that have been carved into the surface that"
      + " spell: Yogsothoth.\n");

    add_exit("3_hall6", "east");
    add_exit("3_hall7", "southeast");
    add_exit("3_pit", "south", check_exit, 1, 0);
    add_exit("3_hall3", "southwest");
    add_exit("3_hall4", "west");

    set_no_exit_msg( ({ "northwest", "north", "northeast" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_pentagram_room */
