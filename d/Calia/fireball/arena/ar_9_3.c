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
    make_arena_room(9, 3, 8, 8);
    add_exit(FIREBALL_ARENA+"ar_9_4","north");
    add_exit(FIREBALL_ARENA+"ar_8_3","west");
    add_exit(FIREBALL_ARENA+"ar_10_4","northeast");
    add_exit(FIREBALL_ARENA+"ar_8_4","northwest");
    add_exit(FIREBALL_ARENA+"ar_8_2","southwest");
}
