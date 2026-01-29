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
    make_arena_room(8, 10, 7, 1);
    add_exit(FIREBALL_ARENA+"ar_8_9","south");
    add_exit(FIREBALL_ARENA+"ar_7_10","west");
    add_exit(FIREBALL_ARENA+"ar_7_11","northwest");
    add_exit(FIREBALL_ARENA+"ar_9_9","southeast");
    add_exit(FIREBALL_ARENA+"ar_7_9","southwest");
}
