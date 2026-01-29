/*
 *  /d/Sparkle/area/orc_temple/2_jailer.c
 *
 *  These are the jailer's quarters on the 2nd level of the Orc Dungeons
 *  in Sparkle
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("in a large square chamber");
    set_long("This is a large, square chamber that has been filled"
      + " with miscellaneous artifacts. A heap in one corner resembles"
      + " a bed of some sort. South, a door-like opening leads"
      + " out onto a corridor. The smell here is thick.\n\n");

    try_item( ({ "here", "area", "room", "chamber", 
                 "large chamber", "square chamber",
                 "large square chamber" }),
        "This room appears to be the personal quarters of someone."
      + " Someone horribly foul.\n");
    try_item( ({ "artifacts", "miscellaneous artifacts" }),
        "There are all sorts of odd things here. It looks like the"
      + " sort of collection that would develop by someone who took"
      + " the personal effects from prisoners and kept them for"
      + " themselves.\n");
    try_item( ({ "effect", "effects", "personal effect",
                 "personal effects" }),
        "All of these things must have belonged to the miserable"
      + " occupants and former occupants of the various prison"
      + " cells.\n");
    try_item( ({ "heap", "bed", "corner", "one corner" }),
        "Is this really a bed? It looks barely suitable for a chicken"
      + " let alone a person.\n");
    add_cmd_item( ({ "bed", "heap",
                     "on bed", "on heap",
                     "down on bed", "down on heap" }),
                  ({ "sleep", "lie", "lay", "rest" }),
        "The thing looks positively foul! You've better things to do"
      + " than sullying every part of your body with the scum left"
      + " behind by a sleeping orc.\n");
    try_item( ({ "opening", "south", "door-like opening",
                 "door like opening" }),
        "It leads out of the chamber into the corridor.\n");
    try_item( ({ "door" }),
        "No door. Just opening.\n");
    try_item( ({ "corridor" }),
        "You'll have to head south to get a look at it.\n");
    try_item( ({ "smell" }),
        "Smells like ... like ... like bad stuff. Actually, the smell"
      + " in here is less horrible than out in the corridor. It must"
      + " be the prison cells themselves which stink so badly.\n");
    try_item( ({ "prison cell", "cell", "cells", "prison cells" }),
        "They aren't visible here.\n");
    try_item( ({ "prison" }),
        "You can't really view the prison itself from in here.\n");
    try_item( ({ "scum" }),
        "Better on the bed than on you.\n");

    add_dungeon_items();
    add_npc(NPC_DIR + "jailer", 1, &->arm_me());

    add_exit("2_hall9", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "north", "east",
                        "southwest", "northwest", "west" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
} /* init */
