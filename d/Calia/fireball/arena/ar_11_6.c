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
    make_arena_room(11, 6, 10, 5);
    add_exit(FIREBALL_ARENA+"ar_11_7","north");
    add_exit(FIREBALL_ARENA+"ar_11_5","south");
    add_exit(FIREBALL_ARENA+"ar_10_6","west");
    add_exit(FIREBALL_ARENA+"ar_10_7","northwest");
    add_exit(FIREBALL_ARENA+"ar_10_5","southwest");
}
