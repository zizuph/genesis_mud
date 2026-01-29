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
    make_arena_room(10, 8, 9, 3);
    add_exit(FIREBALL_ARENA+"ar_10_7","south");
    add_exit(FIREBALL_ARENA+"ar_9_8","west");
    add_exit(FIREBALL_ARENA+"ar_9_9","northwest");
    add_exit(FIREBALL_ARENA+"ar_11_7","southeast");
    add_exit(FIREBALL_ARENA+"ar_9_7","southwest");
}
