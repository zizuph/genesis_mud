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
    make_arena_room(7, 5, 6, 6);
    add_exit(FIREBALL_ARENA+"ar_7_4","south");
    add_exit(FIREBALL_ARENA+"ar_8_5","east");
    add_exit(FIREBALL_ARENA+"ar_8_6","northeast");
    add_exit(FIREBALL_ARENA+"ar_8_4","southeast");
    add_exit(FIREBALL_ARENA+"ar_6_4","southwest");
}
