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
    make_arena_room(4, 6, 3, 5);
    add_exit(FIREBALL_ARENA+"ar_4_7","north");
    add_exit(FIREBALL_ARENA+"ar_4_5","south");
    add_exit(FIREBALL_ARENA+"ar_3_6","west");
    add_exit(FIREBALL_ARENA+"ar_5_7","northeast");
    add_exit(FIREBALL_ARENA+"ar_3_7","northwest");
    add_exit(FIREBALL_ARENA+"ar_5_5","southeast");
    add_exit(FIREBALL_ARENA+"ar_3_5","southwest");
}
