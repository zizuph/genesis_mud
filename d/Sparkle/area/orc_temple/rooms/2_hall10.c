/*
 *  /d/Sparkle/area/orc_temple/2_hall10.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 2.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
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
    set_short("at an intersection between three corridors");
    set_long("The east-west corridor in which you stand is joined"
      + " by a short passage leading north toward what appear to"
      + " be stairs in that direction. The smell here is truly"
      + " dreadful.\n\n");

    try_item( ({ "intersection", "here", "east-west corridor",
                 "corridor" }),
        "The corridor you stand in runs east and west, heading"
      + " toward what appear to be prison cells in each direction.\n");
    try_item( ({ "passage", "short passage", "north" }),
        "To the north, there appear to be some stairs.\n");
    try_item( ({ "stair", "stairs", "stairway" }),
        "The stairs? Oh, they're off to the north. Can't see much"
      + " from here.\n");
    try_item( ({ "corridors", "three corridors" }), 
        "North, west, and east they be, the corridors three!\n");
    try_item( ({ "corridors three" }),
        "They branch like a tree!\n");
    try_item( ({ "tree", "branch" }),
        "Such a fine sight to see!\n");
    try_item( ({ "fine sight", "sight", "see" }),
        "Aye, the corridors three!\n");
    try_item( ({ "smell", "smells" }),
        "Smells like ... like ... like the legendary poop-owl of"
      + " Stankhollow Dell built a nest on your face!\n");
    try_item( ({ "prison" }),
        "This area of the dungeon looks to be exactly that.\n");
    try_item( ({ "area of the dungeon", "area" }),
        "Look around. Take it all in.\n");
    try_item( ({ "cell", "cells", "prison cell", "prison cells" }),
        "East or west. Either way will take you to them.\n");

    add_dungeon_items();
    add_jail_npcs(5);

    add_exit("2_hall1", "west");
    add_exit("2_down", "north");
    add_exit("2_hall8", "east");

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
