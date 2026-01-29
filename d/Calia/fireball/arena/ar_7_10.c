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
    make_arena_room(7, 10, 6, 1);
    add_exit(FIREBALL_ARENA+"ar_7_11","north");
    add_exit(FIREBALL_ARENA+"ar_7_9","south");
    add_exit(FIREBALL_ARENA+"ar_8_10","east");
    add_exit(FIREBALL_ARENA+"ar_6_10","west");
    add_exit(FIREBALL_ARENA+"ar_6_11","northwest");
    add_exit(FIREBALL_ARENA+"ar_8_9","southeast");
    add_exit(FIREBALL_ARENA+"ar_6_9","southwest");
}
