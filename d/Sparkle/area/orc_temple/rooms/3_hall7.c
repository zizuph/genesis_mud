/*
 *  /d/Sparkle/area/orc_temple/rooms/3_hall7.c
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
    set_side("east");
    set_extraline("A row of skulls lines the eastern wall.");

    add_item( ({ "eastern end", "end" }),
        "Here, you stand at one point of a colossal pentagram that"
      + " is constructed of candles.\n");
    add_item( ({ "skull", "skulls", "row", "row of skulls" }),
        "The skulls are set along the crease where the eastern wall"
      + " meets the floor. Their grinning visages are made all the"
      + " more unsettling in the flickering of the candlelight.\n");
    add_item( ({ "flicker", "flickering", "candlelight", "light" }),
        "Its like Halloween, but without the candy or the fun!\n");
    add_item( ({ "halloween", "candy", "fun" }),
        "You wish.\n");
    add_item( ({ "visage", "visages", "grin", "grinning visage",
                 "grinning visages" }),
        "Ghastly!\n");
    add_item( ({ "eastern wall", "east wall", "east" }),
        "The eastern wall is distinguished by the fact that a row"
      + " of skulls has been placed at its base.\n");
    add_item( ({ "base", "crase" }),
        "There be skulls. Arrrrr ...\n");
    add_item( ({ "tar", "hardened tar" }),
        "Skulls and tar must be all the rage in orcish decor. Somehow,"
      + " this does not come as a surprise.\n");
    add_item( ({ "orcish decor", "decor" }),
        "Maybe this will be on the cover of \"Better Homes &"
      + " Dungeons\" next month.\n");

    add_delay_cmd_item(
        ({ "skull", "skulls", "row", "row of skulls", }),
        "search",
        "searching the row of skulls",
        10,
        "You begin searching the row of skulls.\n",
        "Upon closer inspection, you discover that the skulls have been"
      + " cloven, and only their front half fixed to the base of the"
      + " wall with hardened tar.\n");

    add_exit("3_hall5", "northwest");
    add_exit("3_hall6", "north");
    add_exit("3_hall8", "south");
    add_exit("3_hall1", "southwest");
    add_exit("3_pit", "west", check_exit, 1, 0);

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_pentagram_room */
