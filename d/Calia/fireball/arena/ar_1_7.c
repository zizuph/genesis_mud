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
    make_arena_room(1, 7, 0, 4);
    add_exit(FIREBALL_ARENA+"ar_1_6","south");
    add_exit(FIREBALL_ARENA+"ar_2_7","east");
    add_exit(FIREBALL_ARENA+"ar_2_8","northeast");
    add_exit(FIREBALL_ARENA+"ar_2_6","southeast");
}
