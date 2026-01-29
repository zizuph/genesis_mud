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
    add_name("_runt_key_guard");

    set_short("at the end of a corridor leading north");
    set_long("A long corridor has come to its end here. Dim torchlight"
      + " illuminates the walls where brickwork almost feels like it"
      + " is closing in on you.\n\n");

    try_item( ({ "corridor", "long corridor" }),
        "The corridor travels away from here to the north.\n");
    try_item( ({ "end", "end of the corridor" }),
        "All good things must come to an end. Or, in this case, all"
      + " really gloomy and dank things.\n");
    try_item( ({ "brickwork" }),
        "The bricks are many. The talented bricklayers were, apparently,"
      + " few.\n");
    try_item( ({ "bricklayers", "brick layers", "layers" }),
        "An untalented lot, apparently!\n");
    try_item( ({ "untalented lot" }),
        "Very!\n");
    try_item( ({ "talented bricklayers", "talented brick layers" }),
        "If there were any, they were clearly still in bed the day"
      + " these walls were made.\n");

    add_dungeon_items();

    add_npc(NPC_DIR + "goblin_runt", 3 + (random(3)), &->arm_me());
    add_npc(NPC_DIR + "tough_runt", 1, &->arm_me());

    add_exit("1_hall2", "north");

    set_no_exit_msg( ({ "northeast", "southeast", "east", "southwest",
                        "northwest", "south" }),
        "You boldly stroll directly into a wall. OOOF!\n");

    room_add_object(DOORS_DIR + "1_weapon_e");

    /* If the other room isn't loaded, it can bug when a player tries
     * the exit for the first time, so lets make sure it is loaded.
     */
    (ROOMS_DIR + "1_weaponry")->teleldeningsanka();
    
} /* create_dungeon_room */
