/*
 *  This is a room created for the arena pvp system. It exists on a grid
 *  of over 800 rooms plotted procedurally based on the following map:
 *
 *      /w/Genesis/pvp/arena/arena_map.txt
 *
 *  This file is just a shell. To understand the system, please
 *  reference:
 *
 *      /w/Genesis/pvp/arena/arena_room.c
 *
 *  Created May 2014, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../../defs.h"

inherit ARENA_ROOM;

/*
 * Function name:        create_arena_room
 * Description  :        constructor with area specifics
 */
public void
create_arena_room()
{
    arena_setup();
} /* create_arena_room */
