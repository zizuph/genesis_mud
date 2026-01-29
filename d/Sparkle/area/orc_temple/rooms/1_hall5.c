/*
 *  /d/Sparkle/area/orc_temple/1_hall5.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1.
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
    set_short("at a bend in the corridor ");
    set_long("The dank walls stretch far to the south here where they"
      + " are lost from view in the gloom. A bend in the corridor"
      + " leads also to the west.\n\n");

    try_item( ({ "dank wall", "dank walls" }),
        "These might be the dankest walls you've ever seen. Actually,"
      + " you're probably wrong. There are surely walls just as dank"
      + " just a few steps in any direction.\n");
    try_item( ({ "gloom" }),
        "Dark, depressing, eerie ... you know the stuff.\n");
    try_item( ({ "bend", "bend in the corridor" }),
        "It leads both west and south.\n");

    add_dungeon_items();
    add_npc(NPC_DIR + "goblin_runt", 3 + (random(3)), &->arm_me());

    add_exit("1_hall4", "west");
    add_exit("1_hall6", "south");

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "southwest", "northwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */
