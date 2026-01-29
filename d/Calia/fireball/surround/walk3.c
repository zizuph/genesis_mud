
/* 
 * /d/Calia/fireball/surround/walk3.c
 * 
 * A room in the Firedrome walkway. 
 * 
 * Coded by Maniac@Genesis, August 1997
 * 
 * Copyright (C) Miguel Leith 1997
 */ 

#include "defs.h"
#include FIREBALL_HEADER

inherit FIREBALL_WALKWAY_ROOM; 

void
create_room()
{
    make_walkway_room(0, 0, "northeast-south"); 

    add_exit(FIREBALL_WALKWAY+"walk2", "south"); 
}

