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
    make_arena_room(6, 10, 5, 1);
    add_exit(FIREBALL_ARENA+"ar_6_11","north");
    add_exit(FIREBALL_ARENA+"ar_6_9","south");
    add_exit(FIREBALL_ARENA+"ar_7_10","east");
    add_exit(FIREBALL_ARENA+"ar_5_10","west");
    add_exit(FIREBALL_ARENA+"ar_7_11","northeast");
    add_exit(FIREBALL_ARENA+"ar_5_11","northwest");
    add_exit(FIREBALL_ARENA+"ar_7_9","southeast");
    add_exit(FIREBALL_ARENA+"ar_5_9","southwest");
}
