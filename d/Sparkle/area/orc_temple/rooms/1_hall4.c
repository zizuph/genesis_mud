/*
 *  /d/Sparkle/area/orc_temple/1_hall1.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1.
 *
 *  Created June 2010, by Cooper Sherry (Gorboth)
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
    set_short("a dank corridor within the dungeons");
    set_long("Hard and dank walls stretch east and west here where"
      + " a dimly lit corridor extends into unknown gloom. A short"
      + " passage to the north leads to a stairway in the distance.\n\n");

    try_item( ({ "dank corridor", }),
        "Walls, ceiling, floor ... all dank as can be!\n");
    try_item( ({ "hard wall", "hard walls" }),
        "They are pretty dank, too.\n");
    try_item( ({ "dank wall", "dank walls" }),
        "So dank ... and hard! Walls, walls everywhere walls.\n");
    try_item( ({ "dimly lit corridor" }),
        "The torches help a little, but not nearly enough.\n");
    try_item( ({ "gloom" }),
        "Yes, and unknown gloom at that!\n");
    try_item( ({ "unknown gloom" }),
        "You might THINK you want to know more about the gloom, but"
      + " trust me, you don't.\n");
    try_item( ({ "passage", "short passage", "north" }),
        "Just to the north, a short passage leads toward a staircase"
      + " that leads up.\n");
    try_item( ({ "stair", "stairway", "stairs", "staircase", "steps" }),
        "The stairway is to the north. You'll need to head that direction"
      + " for more information.\n");
    add_cmd_item( ({ "stair", "stairway", "stairs", "staircase", "steps",
                     "up stair", "up stairs", "up stairway", "up steps",
                     "up staircase", "up", "down" }),
                  ({ "climb" }),
        "The stairs are to the north. If you're really interested in"
      + " them, you'll need to make that dreadful journey first.\n");

    add_dungeon_items();
    add_npc(NPC_DIR + "goblin_runt", 3 + (random(3)), &->arm_me());

    add_exit("1_up", "north");
    add_exit("1_hall5", "east");
    add_exit("1_hall3", "west");

    set_no_exit_msg( ({ "northeast", "southeast", "south", "southwest",
                        "northwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */
