/*
 *  /d/Sparkle/area/orc_temple/2_hall1.c
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

    set_short("at the southern end of a long prison corridor");
    set_long("Cell doors line the west wall of the corridor that"
      + " stretches north into the distance. East, the corridor"
      + " heads towards what appears to be more cells in that"
      + " direction. The smell is so bad it is literally painful"
      + " to inhale.\n\n");

    try_item( ({ "cell", "cells", "prison cell", "prison cells",
                 "corridor of prison cells",
                 "long corridor", "prison corridor",
                 "long prison corridor", "corridor",
                 "passage", "hall", "hallway" }),
        "All along the western wall that heads north, cell doors"
      + " have been set. This is definitely a prison.\n");
    try_item( ({ "west wall", "western wall", "west" }),
        "It's got that death-is-better-than-here feeling.\n");
    try_item( ({ "feeling", "death-is-better-than-here",
                 "death-is-better-than-here feeling",
                 "death is better than here feeling" }),
        "From the smell, it sounds like quite a few of the"
      + " inhabitants have experienced the feeling to completion.\n");
    try_item( ({ "smell", "smells", }),
        "Smells like ... like ... like you died, rotted, and were"
      + " stuck in your own corpse and forced to smell the process up"
      + " close!\n");
    try_item( ({ "more cells" }),
        "You'd have to head over there to see for yourself.\n");

    add_dungeon_items();
    add_jail_npcs(3);

    door = clone_object(DOORS_DIR + "2_cell_door");
    door->configure_cell_door("west");
    door->set_other_room(ROOMS_DIR + "2_cell1");
    door->move(this_object());

    add_exit("2_hall2", "north");
    add_exit("2_hall10", "east");

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
