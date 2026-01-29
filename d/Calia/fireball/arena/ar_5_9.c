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
    make_arena_room(5, 9, 4, 2);
    add_exit(FIREBALL_ARENA+"ar_5_10","north");
    add_exit(FIREBALL_ARENA+"ar_5_8","south");
    add_exit(FIREBALL_ARENA+"ar_6_9","east");
    add_exit(FIREBALL_ARENA+"ar_4_9","west");
    add_exit(FIREBALL_ARENA+"ar_6_10","northeast");
    add_exit(FIREBALL_ARENA+"ar_4_10","northwest");
    add_exit(FIREBALL_ARENA+"ar_6_8","southeast");
    add_exit(FIREBALL_ARENA+"ar_4_8","southwest");
}
