/*
 *  /d/Sparkle/area/orc_temple/1_hall3.c
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
    set_long("The main corridor rounds a bend here heading south"
      + " and east into the gloom. A low archway opens in the western"
      + " wall leading into a large chamber of some sort.\n\n");

    try_item( ({ "main corridor" }),
        "You're standing in it.\n");
    try_item( ({ "bend" }),
        "Sort of like a straightaway, except completely different.\n");
    try_item( ({ "gloom" }),
        "Gloomy, that.\n");
    try_item( ({ "arch", "archway", "low arch", "low archway" }),
        "The archway is very crudely constructed, amounting to little"
      + " more than a doorway without a door involved.\n");
    try_item( ({ "doorway" }),
        "It's more of an archway, really.\n");
    try_item( ({ "door" }),
        "Door? There's no door here.\n");
    try_item( ({ "chamber", "large chamber" }),
        "You'd probably need to head west to know more about it.\n");

    add_dungeon_items();
    add_npc(NPC_DIR + "goblin_runt", 3 + (random(3)), &->arm_me());

    add_exit("1_barracks1", "west");
    add_exit("1_hall4", "east");
    add_exit("1_hall2", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "north", "southwest",
                        "northwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */
