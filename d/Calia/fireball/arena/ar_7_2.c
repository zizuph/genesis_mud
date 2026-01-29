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
    make_arena_room(7, 2, 6, 9);
    add_exit(FIREBALL_ARENA+"ar_7_3","north");
    add_exit(FIREBALL_ARENA+"ar_7_1","south");
    add_exit(FIREBALL_ARENA+"ar_8_2","east");
    add_exit(FIREBALL_ARENA+"ar_6_2","west");
    add_exit(FIREBALL_ARENA+"ar_8_3","northeast");
    add_exit(FIREBALL_ARENA+"ar_6_3","northwest");
    add_exit(FIREBALL_ARENA+"ar_6_1","southwest");
}
