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
    make_arena_room(5, 11, 4, 0);
    add_exit(FIREBALL_ARENA+"ar_5_10","south");
    add_exit(FIREBALL_ARENA+"ar_6_11","east");
    add_exit(FIREBALL_ARENA+"ar_6_10","southeast");
    add_exit(FIREBALL_ARENA+"ar_4_10","southwest");
}
