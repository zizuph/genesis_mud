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
    make_arena_room(4, 7, 3, 4);
    add_exit(FIREBALL_ARENA+"ar_4_8","north");
    add_exit(FIREBALL_ARENA+"ar_4_6","south");
    add_exit(FIREBALL_ARENA+"ar_5_7","east");
    add_exit(FIREBALL_ARENA+"ar_3_7","west");
    add_exit(FIREBALL_ARENA+"ar_5_8","northeast");
    add_exit(FIREBALL_ARENA+"ar_3_8","northwest");
    add_exit(FIREBALL_ARENA+"ar_3_6","southwest");
}
