
/* 
 * /d/Calia/fireball/surround/walk2.c
 * 
 * A room in the Firedrome walkway. 
 * 
 * Coded by Maniac@Genesis, August 1997
 * 
 * Copyright (C) Miguel Leith 1997
 */ 

#include "defs.h"
#include FIREBALL_HEADER

#define ROAD_CONNECT "/d/Calia/gelan/rooms/north_road_e3"

inherit FIREBALL_WALKWAY_ROOM; 

void
create_room()
{
    make_walkway_room(1, "east", "north-south"); 

    add_exit(ROAD_CONNECT, "southwest"); 
    add_exit(FIREBALL_FOYER, "east"); 
    add_exit(FIREBALL_WALKWAY+"walk1", "south"); 
    add_exit(FIREBALL_WALKWAY+"walk3", "north"); 
}
