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
    make_arena_room(10, 6, 9, 5);
    add_exit(FIREBALL_ARENA+"ar_10_7","north");
    add_exit(FIREBALL_ARENA+"ar_10_5","south");
    add_exit(FIREBALL_ARENA+"ar_11_6","east");
    add_exit(FIREBALL_ARENA+"ar_9_6","west");
    add_exit(FIREBALL_ARENA+"ar_11_7","northeast");
    add_exit(FIREBALL_ARENA+"ar_9_7","northwest");
    add_exit(FIREBALL_ARENA+"ar_11_5","southeast");
    add_exit(FIREBALL_ARENA+"ar_9_5","southwest");
}
