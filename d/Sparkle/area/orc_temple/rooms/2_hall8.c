/*
 *  /d/Sparkle/area/orc_temple/2_hall8.c
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

    set_short("at the south end of a corridor lined with prison cells");
    set_long("A long corridor travels north past prison cells that"
      + " line the eastern wall. West, the passage rounds a bend and"
      + " heads towards what appears to be more cells in the distance"
      + " in that direction.\n\n");

    try_item( ({ "cell", "cells", "prison cell", "prison cells" }),
        "The nearest cell door looks like your best chance to get"
      + " a better look.\n");
    try_item( ({ "corridor", "passage", "hall", "hallway",
                 "long corridor corridor" }),
        "The corridor rounds a bend here, heading both north and"
      + " west.\n");
    try_item( ({ "bend", "corner" }),
        "Sort of like a right angle, but you can walk it.\n");
    try_item( ({ "right angle" }),
        "You know ... ninety degrees.\n");
    try_item( ({ "ninety degrees", "degrees", "90 degrees" }),
        "Yes. Now you get an A+.\n");
    try_item( ({ "east wall", "eastern wall", "east" }),
        "The eastern wall is where the prison cells are located.\n");
    try_item( ({ "prison" }),
        "Sorrow, death, torture, unthinkable smells - this one's"
      + " got 'em all!\n");
    try_item( ({ "sorrow", "death", "torture" }),
        "You've probably caused a bit of that yourself while you've"
      + " been here, actually.\n");
    try_item( ({ "more cells", "distance" }),
        "Off to the west you see what appears to be a similar"
      + " corridor running north.\n");
    try_item( ({ "similar corridor" }),
        "You'll have to head over there to get a closer look.\n");
    try_item( ({ "smell", "smells", "unthinkable smell",
                 "unthinkable smells" }),
        "Smells like ... like ... like a pumpkin that has been hollowed"
      + " out, filled with fish liver, and then left beside a dead"
      + " hog for five weeks!\n");

    add_dungeon_items();
    add_jail_npcs(3);

    door = clone_object(DOORS_DIR + "2_cell_door");
    door->configure_cell_door("east");
    door->set_other_room(ROOMS_DIR + "2_cell8");
    door->move(this_object());

    add_exit("2_hall7", "north");
    add_exit("2_hall10", "west");

    set_no_exit_msg( ({ "northeast", "southeast", "south",
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
