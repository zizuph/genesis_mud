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
    make_arena_room(8, 3, 7, 8);
    add_exit(FIREBALL_ARENA+"ar_8_4","north");
    add_exit(FIREBALL_ARENA+"ar_8_2","south");
    add_exit(FIREBALL_ARENA+"ar_9_3","east");
    add_exit(FIREBALL_ARENA+"ar_7_3","west");
    add_exit(FIREBALL_ARENA+"ar_9_4","northeast");
    add_exit(FIREBALL_ARENA+"ar_7_4","northwest");
    add_exit(FIREBALL_ARENA+"ar_7_2","southwest");
}
