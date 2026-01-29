/*
 *  /d/Emerald/common/guild/aod/rooms/cave_room.c
 *
 *  This is the room master for area descriptions and settings in the
 *  caves which house the Army of Darkness guild in Emerald.
 *
 *  Copyright (c) July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

#include <stdproperties.h> /* for ROOM_I_INSIDE */

/* Prototypes */
public void        create_cave_room();
nomask void        create_emerald_room();



/*
 * Function name:        create_cave_room
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_cave_room()
{
} /* create_cave_room */


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room with domain presets
 */
nomask void
create_emerald_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    create_cave_room();
} /* create_emerald_room */


/*
 * Function name:        add_cave_items
 * Description  :        include add_items which are appropriate for 
 *                       cave areas surrounding the guild.
 */
public void
add_cave_items()
{
    try_item( ({ "cave", "cavern", "area", "guild", "here", "caves" }),
        "These caves appear to be the product of massively destructive"
      + " efforts on the part of frighteningly strong beings. The"
      + " walls of rock bear testimony to this.\n");
    try_item( ({ "sky" }),
        "The sky is not visible from inside these caves.\n");
    try_item( ({ "wall", "walls", "cave wall", "cave walls",
                 "cavern wall", "cavern walls", "wall of the cavern",
                 "walls of the cavern", "rock", "rock wall",
                 "rock walls", "walls of rock" }),
        "The walls of these caverns are extremely rough and broken"
      + " looking. It almost appears as if they had been beaten into"
      + " shape by huge bludgeoning devices - possibly even fists!\n");
    try_item( ({ "ground", "down", "floor", "terrain",
                 "rocky terrain" }),
        "The floor of the caves is rough and uneven.\n");
    try_item( ({ "mountain", "mountains", "blackwall mountains" }),
        "You are deep within the Blackwall Mountains. Its hard to"
      + " get much of an appreciation for them other than the fact"
      + " that they are most definitely made of solid rock.\n");
    try_item( ({ "ceiling", "roof", "up" }),
        "The roof of the tunnel at least twenty-five feet above"
      + " the floor. These tunnels are massive!\n");
} /* add_cave_items */