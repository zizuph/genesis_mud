/*
 *  /d/Sparkle/area/orc_temple/2_hall4.c
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

    set_short("at the north end of a corridor of prison cells");
    set_long("A corridor of prison cells extends to the south"
      + " of this bend in the passage. East, a similar-looking"
      + " area of cells appears to be on the other side of the"
      + " dungeon. The smell here is unbelievable.\n\n");

    try_item( ({ "cell", "cells", "prison cell", "prison cells",
                 "corridor of prison cells", }),
        "Prison cells extend along the west wall all along the"
      + " corridor heading south from here.\n");
    try_item( ({ "corridor", "passage", "hall", "hallway",
                 "long corridor" }),
        "The corridor rounds a bend here, heading both south and"
      + " east.\n");
    try_item( ({ "bend", "corner" }),
        "The corner does what corners do - it goes two different"
      + " directions.\n");
    try_item( ({ "direction", "directions", "different directions",
                 "two directions", "two different directions" }),
        "In this case, south and east.\n");
    try_item( ({ "west wall", "western wall", "west" }),
        "The western wall is set with many prison cells.\n");
    try_item( ({ "prison" }),
        "Sorrow, death, torture, unthinkable smells - this one's"
      + " got 'em all!\n");
    try_item( ({ "sorrow", "death", "torture" }),
        "You've probably caused a bit of that yourself while you've"
      + " been here, actually.\n");
    try_item( ({ "similar-looking area", "area of cells",
                 "similar-looking area of cells" }),
        "You'll have to head over there to get a closer look.\n");
    try_item( ({ "smell", "smells", "unthinkable smell",
                 "unthinkable smells" }),
        "Smells like ... like ... like a filet of rotten bear"
      + " carcass soaked in stomach acid!\n");

    add_dungeon_items();
    add_jail_npcs(3);

    door = clone_object(DOORS_DIR + "2_cell_door");
    door->configure_cell_door("west");
    door->set_other_room(ROOMS_DIR + "2_cell4");
    door->move(this_object());

    add_exit("2_hall9", "east");
    add_exit("2_hall3", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "north",
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
