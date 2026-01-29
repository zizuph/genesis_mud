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
    make_arena_room(11, 7, 10, 4);
    add_exit(FIREBALL_ARENA+"ar_11_6","south");
    add_exit(FIREBALL_ARENA+"ar_10_7","west");
    add_exit(FIREBALL_ARENA+"ar_10_8","northwest");
    add_exit(FIREBALL_ARENA+"ar_10_6","southwest");
}
