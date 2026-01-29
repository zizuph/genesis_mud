/*
 *  /d/Sparkle/area/tutorial/cliffs/cliffroad_2.c
 *
 *  A road in the cliffs leading toward Krolock's castle. There
 *  is a cave to the west.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* prototypes */
public void        create_silverdell();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("on a path in the cliffs beside a cave");
    set_long("A narrow path winds its way up into the ever steepening"
      + " cliffs, travelling north and southeast. A dark cave opens"
      + " on to the trail to the west.\n\n");

    add_outdoor_items();
    add_cliffs_items();

    add_item( ({ "here", "area" }), long);
    add_item( ({ "cave", "cave opening", "opening", "dark cave",
                 "dark opening", "dark cave opening", "west" }),
        "To the west, the otherwise sheer surface of the cliffs" 
      + " is interrupted by a dark cave opening.\n");

    add_exit("cliffroad_3", "north");
    add_exit("cliffroad_1", "southeast");
    add_exit("cave", "west");

    //This room is instanced.
    instance_entrance = 0;
} /* create_silverdell */
