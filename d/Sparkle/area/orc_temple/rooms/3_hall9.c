/*
 *  /d/Sparkle/area/orc_temple/rooms/2_hall9.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 3.
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
    object   door;

    set_short("a narrow north-south tunnel");
    set_long("A feeling of horror is thick in your throat as you"
      + " traverse the length of this narrow tunnel. The flickering"
      + " lights from a vast chamber to the north are dimly visible"
      + " in that direction. South, the tunnel rounds a bend and"
      + " disappears from view.\n\n");

    add_item( ({ "alcove", "eastern wall", "east wall" }),
        "A polished cedar door is set within the alcove. One presumes"
      + " this must indicate an area beyond.\n");
    add_item( ({ "area beyond" }),
        "HINT: open door, go east\n");
    add_item( ({ "tunnel", "here", "north-south tunnel", "narrow tunnel",
                 "narrow north-south tunnel" }),
        "The tunnel is narrow, and feels a bit constricting. That,"
      + " however, cannot explain the wretched feeling of gnawing horror"
      + " that chokes your mind.\n");
    add_item( ({ "horror", "feeling", "gnawing horror", "wretched feeling",
                 "feeling of horror" }),
        "Here, you are approaching something that no mortal should ever"
      + " encounter. You do not know how you know this ... but you"
      + " KNOW this. It is as if a primal instinct within you senses"
      + " an ancient horror known to all living beings.\n");
    add_item( ({ "ancient horror" }), "@@yogsothoth@@");
    add_item( ({ "flickering", "lights", "flickering lights",
                 "light", "flickering lights" }),
        "The lights are in the chamber to the north, and cannot be"
      + " properly viewed from here.\n");
    add_item( ({ "chamber", "vast chamber", "north" }),
        "As unsettling as the chamber to the north may be, it feels"
      + " almost welcoming compared to the confined sense of"
      + " horror you are experiencing here.\n");
    add_item( ({ "bend", "turn", "corner", "south" }),
        "South, the tunnel rounds a corner and disappears from"
      + " view. As you peer that way, you can almost feel horror"
      + " prickling the backs of your eye sockets.\n");

    add_dungeon_items();

    door = clone_object(DOORS_DIR + "3_priest_w");
    door->move(this_object());

    add_npc(NPC_DIR + "goblin_warrior", 3, &->arm_me());

    add_exit("3_hall8", "north");
    add_exit("3_hall10", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "west",
                        "southwest", "northwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */


/*
 * Function name:        add_dungeon_tells
 * Description  :        Have this room use madness tells.
 */
public void
add_dungeon_tells()
{
    /* No tells in here. Spooky silence. */
} /* add_dungeon_tells */