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
    make_arena_room(9, 9, 8, 2);
    add_exit(FIREBALL_ARENA+"ar_9_8","south");
    add_exit(FIREBALL_ARENA+"ar_8_9","west");
    add_exit(FIREBALL_ARENA+"ar_8_10","northwest");
    add_exit(FIREBALL_ARENA+"ar_10_8","southeast");
    add_exit(FIREBALL_ARENA+"ar_8_8","southwest");
}
