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
    make_arena_room(4, 10, 3, 1);
    add_exit(FIREBALL_ARENA+"ar_4_9","south");
    add_exit(FIREBALL_ARENA+"ar_5_10","east");
    add_exit(FIREBALL_ARENA+"ar_5_11","northeast");
    add_exit(FIREBALL_ARENA+"ar_5_9","southeast");
    add_exit(FIREBALL_ARENA+"ar_3_9","southwest");
}
