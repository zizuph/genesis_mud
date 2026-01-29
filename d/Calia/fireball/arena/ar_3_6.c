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
    make_arena_room(3, 6, 2, 5);
    add_exit(FIREBALL_ARENA+"ar_3_7","north");
    add_exit(FIREBALL_ARENA+"ar_3_5","south");
    add_exit(FIREBALL_ARENA+"ar_4_6","east");
    add_exit(FIREBALL_ARENA+"ar_2_6","west");
    add_exit(FIREBALL_ARENA+"ar_4_7","northeast");
    add_exit(FIREBALL_ARENA+"ar_2_7","northwest");
    add_exit(FIREBALL_ARENA+"ar_4_5","southeast");
    add_exit(FIREBALL_ARENA+"ar_2_5","southwest");
}
