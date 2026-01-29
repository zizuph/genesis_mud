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
    make_arena_room(3, 7, 2, 4);
    add_exit(FIREBALL_ARENA+"ar_3_8","north");
    add_exit(FIREBALL_ARENA+"ar_3_6","south");
    add_exit(FIREBALL_ARENA+"ar_4_7","east");
    add_exit(FIREBALL_ARENA+"ar_2_7","west");
    add_exit(FIREBALL_ARENA+"ar_4_8","northeast");
    add_exit(FIREBALL_ARENA+"ar_2_8","northwest");
    add_exit(FIREBALL_ARENA+"ar_4_6","southeast");
    add_exit(FIREBALL_ARENA+"ar_2_6","southwest");
}
