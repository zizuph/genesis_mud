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
    make_arena_room(5, 2, 4, 9);
    add_exit(FIREBALL_ARENA+"ar_5_3","north");
    add_exit(FIREBALL_ARENA+"ar_5_1","south");
    add_exit(FIREBALL_ARENA+"ar_6_2","east");
    add_exit(FIREBALL_ARENA+"ar_4_2","west");
    add_exit(FIREBALL_ARENA+"ar_6_3","northeast");
    add_exit(FIREBALL_ARENA+"ar_4_3","northwest");
    add_exit(FIREBALL_ARENA+"ar_6_1","southeast");
}
