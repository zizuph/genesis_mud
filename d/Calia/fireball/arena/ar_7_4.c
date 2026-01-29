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
    make_arena_room(7, 4, 6, 7);
    add_exit(FIREBALL_ARENA+"ar_7_5","north");
    add_exit(FIREBALL_ARENA+"ar_7_3","south");
    add_exit(FIREBALL_ARENA+"ar_8_4","east");
    add_exit(FIREBALL_ARENA+"ar_6_4","west");
    add_exit(FIREBALL_ARENA+"ar_8_5","northeast");
    add_exit(FIREBALL_ARENA+"ar_8_3","southeast");
    add_exit(FIREBALL_ARENA+"ar_6_3","southwest");
}
