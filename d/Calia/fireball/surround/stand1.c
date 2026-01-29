
/* 
 * /d/Calia/fireball/surround/stand1.c
 * 
 * A room in the Firedrome stand. 
 * 
 * Coded by Maniac@Genesis, 22/7/97
 * 
 * Copyright (C) Miguel Leith 1997
 */ 

#include "defs.h"
#include FIREBALL_HEADER

inherit FIREBALL_STAND_ROOM; 

void
create_room()
{
    make_stand_room(); 

    add_exit(FIREBALL_STAND+"stand2", "north"); 
}

