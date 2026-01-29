/*
 *  /d/Sparkle/area/orc_temple/2_hall3.c
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

    set_short("a corridor lined with cell doors");
    set_long("Cell doors line the corridor both to the north and"
      + " south. The eastern wall has a large ghash in it just"
      + " above a dimly burning torch. The smell is almost enough"
      + " to make one swoon.\n\n");

    try_item( ({ "cell", "cells", "prison cell", "prison cells",
                 "corridor of prison cells", }),
        "Prison cells extend along the west wall both to the"
      + " north and south along the corridor.\n");
    try_item( ({ "corridor", "passage", "hall", "hallway",
                 "long corridor" }),
        "This area of the dungeon is clearly a prison.\n");
    try_item( ({ "east wall", "eastern wall", "east" }),
        "The wall to the east has an unusual ghash in its otherwise"
      + " typical surface.\n");
    try_item( ({ "typical surface", "surface" }),
        "Yep, typical ... oh, except for the ghash.\n");
    try_item( ({ "ghash", "unusual ghash", "large ghash" }),
        "The ghash is about 5 feet long and a foot deep. Even the"
      + " strongest ogre would be hard pressed to put something"
      + " like this in the wall. Strange ...\n");
    try_item( ({ "dimly burning torch" }),
        "The flames from the torch illuminate the ghash positioned"
      + " just a few inches above.\n");
    try_item( ({ "west wall", "western wall", "west" }),
        "The western wall is set with many prison cells.\n");
    try_item( ({ "prison" }),
        "There is no mistaking it. You've got cells, you've got smells,"
      + " you've got bloody hells.\n");
    try_item( ({ "bloody hell", "bloody hells", "hell", "hells" }),
        "Well, that is what I'd shout if I was locked in, anyway.\n");
    try_item( ({ "smell", "smells", }),
        "Smells like ... like ... like someone puked in their bed,"
      + " rolled around in it, died, and then puked again!\n");

    add_dungeon_items();
    add_jail_npcs(3);

    door = clone_object(DOORS_DIR + "2_cell_door");
    door->configure_cell_door("west");
    door->set_other_room(ROOMS_DIR + "2_cell3");
    door->move(this_object());

    add_exit("2_hall4", "north");
    add_exit("2_hall2", "south");

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
