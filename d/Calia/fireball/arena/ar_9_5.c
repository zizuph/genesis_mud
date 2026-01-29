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
    make_arena_room(9, 5, 8, 6);
    add_exit(FIREBALL_ARENA+"ar_9_6","north");
    add_exit(FIREBALL_ARENA+"ar_9_4","south");
    add_exit(FIREBALL_ARENA+"ar_10_5","east");
    add_exit(FIREBALL_ARENA+"ar_8_5","west");
    add_exit(FIREBALL_ARENA+"ar_10_6","northeast");
    add_exit(FIREBALL_ARENA+"ar_8_6","northwest");
    add_exit(FIREBALL_ARENA+"ar_10_4","southeast");
    add_exit(FIREBALL_ARENA+"ar_8_4","southwest");
}
