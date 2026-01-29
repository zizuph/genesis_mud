/*
 *  /d/Sparkle/area/tutorial/castle/hallway_2s.c
 *
 *  Within the castle of Baron von Krolock.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

/* Prototypes */
public void        create_castle_room();


/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("in a long east-west corridor");
    set_long("You stand in the middle of a long corridor that travels"
      + " both east and west. There is a sense of hostility in this"
      + " castle. The walls feel as if they are pressing in on you,"
      + " bearing down on your senses with their hideous images.\n\n");

    add_item( ({ "west", "east", "corridor", "corridors",
                 "long corridor", "long corridors" }),
        "The walls of this corridor are lined with torches whose light"
      + " seems to flicker in an almost unnatural way upon the faces"
      + " of the many tapestries which hang upon the walls.\n");

    add_castle_items();
    add_torch_items();

    add_exit("hallway_3s", "west");
    add_exit("hallway_1s", "east");

    reset_room();
} /* create_castle_room */
