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
    make_arena_room(4, 2, 3, 9);
    add_exit(FIREBALL_ARENA+"ar_4_3","north");
    add_exit(FIREBALL_ARENA+"ar_5_2","east");
    add_exit(FIREBALL_ARENA+"ar_5_3","northeast");
    add_exit(FIREBALL_ARENA+"ar_3_3","northwest");
    add_exit(FIREBALL_ARENA+"ar_5_1","southeast");
}
