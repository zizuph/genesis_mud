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
    make_arena_room(10, 4, 9, 7);
    add_exit(FIREBALL_ARENA+"ar_10_5","north");
    add_exit(FIREBALL_ARENA+"ar_9_4","west");
    add_exit(FIREBALL_ARENA+"ar_11_5","northeast");
    add_exit(FIREBALL_ARENA+"ar_9_5","northwest");
    add_exit(FIREBALL_ARENA+"ar_9_3","southwest");
}
