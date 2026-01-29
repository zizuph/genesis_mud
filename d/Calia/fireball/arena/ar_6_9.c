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
    make_arena_room(6, 9, 5, 2);
    add_exit(FIREBALL_ARENA+"ar_6_10","north");
    add_exit(FIREBALL_ARENA+"ar_6_8","south");
    add_exit(FIREBALL_ARENA+"ar_7_9","east");
    add_exit(FIREBALL_ARENA+"ar_5_9","west");
    add_exit(FIREBALL_ARENA+"ar_7_10","northeast");
    add_exit(FIREBALL_ARENA+"ar_5_10","northwest");
    add_exit(FIREBALL_ARENA+"ar_7_8","southeast");
    add_exit(FIREBALL_ARENA+"ar_5_8","southwest");
}
