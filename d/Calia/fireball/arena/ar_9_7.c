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
    make_arena_room(9, 7, 8, 4);
    add_exit(FIREBALL_ARENA+"ar_9_8","north");
    add_exit(FIREBALL_ARENA+"ar_9_6","south");
    add_exit(FIREBALL_ARENA+"ar_10_7","east");
    add_exit(FIREBALL_ARENA+"ar_8_7","west");
    add_exit(FIREBALL_ARENA+"ar_10_8","northeast");
    add_exit(FIREBALL_ARENA+"ar_8_8","northwest");
    add_exit(FIREBALL_ARENA+"ar_10_6","southeast");
    add_exit(FIREBALL_ARENA+"ar_8_6","southwest");
}
