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
    make_arena_room(7, 3, 6, 8);
    add_exit(FIREBALL_ARENA+"ar_7_4","north");
    add_exit(FIREBALL_ARENA+"ar_7_2","south");
    add_exit(FIREBALL_ARENA+"ar_8_3","east");
    add_exit(FIREBALL_ARENA+"ar_6_3","west");
    add_exit(FIREBALL_ARENA+"ar_8_4","northeast");
    add_exit(FIREBALL_ARENA+"ar_6_4","northwest");
    add_exit(FIREBALL_ARENA+"ar_8_2","southeast");
    add_exit(FIREBALL_ARENA+"ar_6_2","southwest");
}
