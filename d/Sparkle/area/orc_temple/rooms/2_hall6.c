/*
 *  /d/Sparkle/area/orc_temple/2_hall6.c
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
    set_long("The row of prison cells continues to the north and"
      + " south here. The smell continues to assault your senses,"
      + " and there is a palpable sense of despair throughout this"
      + " part of the dungeon.\n\n");

    try_item( ({ "row", "row of cells", "row of prison cells" }),
        "Awww ... look at the cells ... all cute in a row. Wait, that"
      + " isn't cute.\n");
    try_item( ({ "smell", "smells" }),
        "Smells like ... like ... like a bucket of shredded sheep"
      + " anus!\n");
    try_item( ({ "despair", "sense of despair", 
                 "palpable sense of despair" }),
        "The accounts of torment and tragedy that have taken place"
      + " here would be too many to count, if there were any"
      + " survivors to tell them.\n");
    try_item( ({ "survivor", "survivors" }),
        "Unlikely.\n");
    try_item( ({ "prison" }),
        "Unlike most prisons, this one is run by the criminals and"
      + " locks up the innocents.\n");
    try_item( ({ "criminal", "criminals" }),
        "Look around. They grunt a lot.\n");
    try_item( ({ "innocent", "innocents" }),
        "Tragic!\n");

    add_dungeon_items();
    add_jail_npcs(3);

    door = clone_object(DOORS_DIR + "2_cell_door");
    door->configure_cell_door("east");
    door->set_other_room(ROOMS_DIR + "2_cell6");
    door->move(this_object());

    add_exit("2_hall5", "north");
    add_exit("2_hall7", "south");

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
