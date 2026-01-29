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
    make_arena_room(2, 5, 1, 6);
    add_exit(FIREBALL_ARENA+"ar_2_6","north");
    add_exit(FIREBALL_ARENA+"ar_2_4","south");
    add_exit(FIREBALL_ARENA+"ar_3_5","east");
    add_exit(FIREBALL_ARENA+"ar_1_5","west");
    add_exit(FIREBALL_ARENA+"ar_3_6","northeast");
    add_exit(FIREBALL_ARENA+"ar_1_6","northwest");
    add_exit(FIREBALL_ARENA+"ar_3_4","southeast");
}
