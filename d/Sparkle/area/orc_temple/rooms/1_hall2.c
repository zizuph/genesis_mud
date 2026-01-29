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
    set_short("a dank north-south corridor");
    set_long("The walls feel very close on both sides here, narrowing"
      + " slightly in both the north and south direction as the"
      + " corridor travels onward. A feeling of ill-ease hangs heavily"
      + " in this place.\n\n");

    try_item( ({ "corridor", "dank corridor", "north-south corridor",
                 "dank north-south corridor" }),
        "It's all around you.\n");
    try_item( ({ "feeling", "feeling of ill ease",
                 "feeling of ill-ease" }),
        "Getting in touch with your feelings is one thing. Trying to"
      + " examine them requires a long couch and a psychologist."
      + " Unfortunately, all the psychologists in Genesis were wiped"
      + " out in the Great Public Bath Disaster of 4320.\n");
    try_item( ({ "psychologist", "psychologists" }),
        "Gone! Wiped out! Sad, really.\n");
    try_item( ({ "couch", "long couch" }),
        "You really do seem to need one, don't you?\n");
    try_item( ({ "place", "this place" }),
        "It's got that ... HERE feeling.\n");

    add_dungeon_items();
    add_npc(NPC_DIR + "goblin_runt", 3 + (random(3)), &->arm_me());

    add_exit("1_hall3", "north");
    add_exit("1_hall1", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "east", "southwest",
                        "northwest", "west" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */
