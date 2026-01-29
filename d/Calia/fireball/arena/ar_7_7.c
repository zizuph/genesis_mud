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
    make_arena_room(7, 7, 6, 4);
    add_exit(FIREBALL_ARENA+"ar_7_8","north");
    add_exit(FIREBALL_ARENA+"ar_8_7","east");
    add_exit(FIREBALL_ARENA+"ar_8_8","northeast");
    add_exit(FIREBALL_ARENA+"ar_6_8","northwest");
    add_exit(FIREBALL_ARENA+"ar_8_6","southeast");
}
