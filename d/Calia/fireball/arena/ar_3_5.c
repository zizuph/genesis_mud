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
    make_arena_room(3, 5, 2, 6);
    add_exit(FIREBALL_ARENA+"ar_3_6","north");
    add_exit(FIREBALL_ARENA+"ar_3_4","south");
    add_exit(FIREBALL_ARENA+"ar_4_5","east");
    add_exit(FIREBALL_ARENA+"ar_2_5","west");
    add_exit(FIREBALL_ARENA+"ar_4_6","northeast");
    add_exit(FIREBALL_ARENA+"ar_2_6","northwest");
    add_exit(FIREBALL_ARENA+"ar_4_4","southeast");
    add_exit(FIREBALL_ARENA+"ar_2_4","southwest");
}
