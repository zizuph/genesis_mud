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
    make_arena_room(5, 5, 4, 6);
    add_exit(FIREBALL_ARENA+"ar_5_4","south");
    add_exit(FIREBALL_ARENA+"ar_4_5","west");
    add_exit(FIREBALL_ARENA+"ar_4_6","northwest");
    add_exit(FIREBALL_ARENA+"ar_6_4","southeast");
    add_exit(FIREBALL_ARENA+"ar_4_4","southwest");
}
