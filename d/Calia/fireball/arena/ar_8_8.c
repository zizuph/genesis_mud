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
    make_arena_room(8, 8, 7, 3);
    add_exit(FIREBALL_ARENA+"ar_8_9","north");
    add_exit(FIREBALL_ARENA+"ar_8_7","south");
    add_exit(FIREBALL_ARENA+"ar_9_8","east");
    add_exit(FIREBALL_ARENA+"ar_7_8","west");
    add_exit(FIREBALL_ARENA+"ar_9_9","northeast");
    add_exit(FIREBALL_ARENA+"ar_7_9","northwest");
    add_exit(FIREBALL_ARENA+"ar_9_7","southeast");
    add_exit(FIREBALL_ARENA+"ar_7_7","southwest");
}
