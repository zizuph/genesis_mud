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
    make_arena_room(3, 4, 2, 7);
    add_exit(FIREBALL_ARENA+"ar_3_5","north");
    add_exit(FIREBALL_ARENA+"ar_3_3","south");
    add_exit(FIREBALL_ARENA+"ar_4_4","east");
    add_exit(FIREBALL_ARENA+"ar_2_4","west");
    add_exit(FIREBALL_ARENA+"ar_4_5","northeast");
    add_exit(FIREBALL_ARENA+"ar_2_5","northwest");
    add_exit(FIREBALL_ARENA+"ar_4_3","southeast");
}
