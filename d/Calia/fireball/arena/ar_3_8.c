/*
 * A room in the Firedrome's arena.
 *
 * Coded by Maniac@Genesis, December 1998
 *
 * Copyright (C) Miguel Leith 1998
 */

#include "defs.h"

#include FIREBALL_HEADER

inherit FIREBALL_ARENA_ROOM;

void
create_room()
{
    make_arena_room(3, 8, 2, 3);
    add_exit(FIREBALL_ARENA+"ar_3_9","north");
    add_exit(FIREBALL_ARENA+"ar_3_7","south");
    add_exit(FIREBALL_ARENA+"ar_4_8","east");
    add_exit(FIREBALL_ARENA+"ar_2_8","west");
    add_exit(FIREBALL_ARENA+"ar_4_9","northeast");
    add_exit(FIREBALL_ARENA+"ar_4_7","southeast");
    add_exit(FIREBALL_ARENA+"ar_2_7","southwest");
}
