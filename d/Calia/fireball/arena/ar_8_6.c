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
    make_arena_room(8, 6, 7, 5);
    add_exit(FIREBALL_ARENA+"ar_8_7","north");
    add_exit(FIREBALL_ARENA+"ar_8_5","south");
    add_exit(FIREBALL_ARENA+"ar_9_6","east");
    add_exit(FIREBALL_ARENA+"ar_9_7","northeast");
    add_exit(FIREBALL_ARENA+"ar_7_7","northwest");
    add_exit(FIREBALL_ARENA+"ar_9_5","southeast");
    add_exit(FIREBALL_ARENA+"ar_7_5","southwest");
}
