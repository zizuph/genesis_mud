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
    make_arena_room(8, 2, 7, 9);
    add_exit(FIREBALL_ARENA+"ar_8_3","north");
    add_exit(FIREBALL_ARENA+"ar_7_2","west");
    add_exit(FIREBALL_ARENA+"ar_9_3","northeast");
    add_exit(FIREBALL_ARENA+"ar_7_3","northwest");
    add_exit(FIREBALL_ARENA+"ar_7_1","southwest");
}
