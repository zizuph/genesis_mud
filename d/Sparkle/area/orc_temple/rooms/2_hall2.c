/*
 *  /d/Sparkle/area/orc_temple/2_hall2.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 2.
 *
 *  Created September 2010, by Cooper Sherry (Gorboth)
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
    object   door;

    set_short("a north-south prison corridor");
    set_long("This north-south prison corridor is lined with many"
      + " cells that emenate a smell that is too horrifying to"
      + " ignore.\n\n");

    try_item( ({ "cell", "cells", "prison cell", "prison cells",
                 "corridor of prison cells", }),
        "There are many prison cells, each set with a door in the"
      + " western wall.\n");
    try_item( ({ "corridor", "passage", "hall", "hallway",
                 "long corridor" }),
        "The distinguishing feature? Cell doors.\n");
    try_item( ({ "west wall", "western wall", "west" }),
        "The western wall is where people don't want to go - the"
      + " lockup.\n");
    try_item( ({ "lockup", "the lockup" }),
        "Whatcha gonna do when they come for you?\n");
    try_item( ({ "prison", "prison corridor",
                 "north-south corridor",
                 "north-south prison corridor" }),
        "If someone were to look up 'prison' in the dictionary,"
      + " there could be a picture of this place. Actually, no"
      + " a picture just wouldn't properly communicate the"
      + " smell.\n");
    try_item( ({ "dictionary" }),
        "Go look it up!\n");
    try_item( ({ "smell", "smells", }),
        "Smells like ... like ... like there is a dead whale nearby"
      + " that committed suicide by swallowing a billion pounds of"
      + " rhinocerous diarrhea!\n");
    try_item( ({ "this place", "place" }),
        "It's not the stuff dreams are made of.\n");
    try_item( ({ "dream", "dreams", "stuff", "stuff dreams are made of",
                 "the stuff dreams are made of" }),
        "Humphry Bogart, you are not.\n");
    try_item( ({ "bogart", "humphry", "humphry bogart" }),
        "Stop Bogarting and start adventuring!\n");

    add_dungeon_items();
    add_jail_npcs(3);

    door = clone_object(DOORS_DIR + "2_cell_door");
    door->configure_cell_door("west");
    door->set_other_room(ROOMS_DIR + "2_cell2");
    door->move(this_object());

    add_exit("2_hall3", "north");
    add_exit("2_hall1", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "east",
                        "southwest", "northwest" }),
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
