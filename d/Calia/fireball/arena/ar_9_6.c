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
    make_arena_room(9, 6, 8, 5);
    add_exit(FIREBALL_ARENA+"ar_9_7","north");
    add_exit(FIREBALL_ARENA+"ar_9_5","south");
    add_exit(FIREBALL_ARENA+"ar_10_6","east");
    add_exit(FIREBALL_ARENA+"ar_8_6","west");
    add_exit(FIREBALL_ARENA+"ar_10_7","northeast");
    add_exit(FIREBALL_ARENA+"ar_8_7","northwest");
    add_exit(FIREBALL_ARENA+"ar_10_5","southeast");
    add_exit(FIREBALL_ARENA+"ar_8_5","southwest");
}
