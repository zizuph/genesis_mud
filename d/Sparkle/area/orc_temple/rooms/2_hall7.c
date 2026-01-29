/*
 *  /d/Sparkle/area/orc_temple/2_hall7.c
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

    set_short("in a long corridor on a row of prison cells");
    set_long("Cells line the eastern wall as you traverse this"
      + " north-south corridor in the dungeon. The smell here"
      + " remains unrelentingly dreadful. You notice a pool"
      + " of liquid on the floor.\n\n");

    try_item( ({ "cell", "cells", "prison cell", "prison cells" }),
        "The nearest cell door looks just about like all the others"
      + " along this corridor.\n");
    try_item( ({ "corridor", "passage", "hall", "hallway",
                 "north-south corridor" }),
        "The hallway is fairly narrow, and distinguished on the"
      + " eastern side with cell doors.\n");
    try_item( ({ "pool", "liquid", "pool of liquid" }),
        "Upon closer inspection you realize that this is actually"
      + " a pool of blood. It has formed at the base of what appears"
      + " to be a chopping block which protrudes from the west wall.\n");
    try_item( ({ "east wall", "eastern wall", "east" }),
        "The eastern wall is where the prison cells are located.\n");
    try_item( ({ "prison" }),
        "Yes, this is exactly that.\n");
    try_item( ({ "blood", "pool of blood" }),
        "The proximity of the blood to the chopping block suggests"
      + " something very nasty happens here.\n");
    try_item( ({ "block", "chopping block" }),
        "You get the grim feeling that this has not been put to use on"
      + " chickens.\n");
    try_item( ({ "chicken", "chickens" }),
        "You suddenly picture a prisoner running around with his head"
      + " cut off. Ghastly!\n");
    try_item( ({ "west wall", "western wall", "west" }),
        "The west wall holds many torches, and a chopping block protrudes"
      + " from it near the floor here.\n");
    try_item( ({ "smell", "smells" }),
        "Smells like ... like ... like a plate of scrambled intestines"
      + " mixed with chopped pickled eggs!\n");

    add_dungeon_items();
    add_jail_npcs(3);

    door = clone_object(DOORS_DIR + "2_cell_door");
    door->configure_cell_door("east");
    door->set_other_room(ROOMS_DIR + "2_cell7");
    door->move(this_object());

    add_exit("2_hall6", "north");
    add_exit("2_hall8", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "west",
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
