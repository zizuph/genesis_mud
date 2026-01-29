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
    make_arena_room(3, 3, 2, 8);
    add_exit(FIREBALL_ARENA+"ar_3_4","north");
    add_exit(FIREBALL_ARENA+"ar_4_3","east");
    add_exit(FIREBALL_ARENA+"ar_4_4","northeast");
    add_exit(FIREBALL_ARENA+"ar_2_4","northwest");
    add_exit(FIREBALL_ARENA+"ar_4_2","southeast");
}
