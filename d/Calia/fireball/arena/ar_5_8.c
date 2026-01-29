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
    make_arena_room(5, 8, 4, 3);
    add_exit(FIREBALL_ARENA+"ar_5_9","north");
    add_exit(FIREBALL_ARENA+"ar_5_7","south");
    add_exit(FIREBALL_ARENA+"ar_6_8","east");
    add_exit(FIREBALL_ARENA+"ar_4_8","west");
    add_exit(FIREBALL_ARENA+"ar_6_9","northeast");
    add_exit(FIREBALL_ARENA+"ar_4_9","northwest");
    add_exit(FIREBALL_ARENA+"ar_4_7","southwest");
}
