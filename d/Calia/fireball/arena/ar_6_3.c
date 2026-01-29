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
    make_arena_room(6, 3, 5, 8);
    add_exit(FIREBALL_ARENA+"ar_6_4","north");
    add_exit(FIREBALL_ARENA+"ar_6_2","south");
    add_exit(FIREBALL_ARENA+"ar_7_3","east");
    add_exit(FIREBALL_ARENA+"ar_5_3","west");
    add_exit(FIREBALL_ARENA+"ar_7_4","northeast");
    add_exit(FIREBALL_ARENA+"ar_5_4","northwest");
    add_exit(FIREBALL_ARENA+"ar_7_2","southeast");
    add_exit(FIREBALL_ARENA+"ar_5_2","southwest");
}
