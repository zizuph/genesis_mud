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
    make_arena_room(5, 1, 4, 10);
    add_exit(FIREBALL_ARENA+"ar_5_2","north");
    add_exit(FIREBALL_ARENA+"ar_6_1","east");
    add_exit(FIREBALL_ARENA+"ar_6_2","northeast");
    add_exit(FIREBALL_ARENA+"ar_4_2","northwest");
}
