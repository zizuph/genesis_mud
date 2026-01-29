/* 
 * The north goal net in the Firedrome Arena
 *
 * Coded by Maniac@Genesis 3/10/98
 *
 * Copyright (C) Miguel Leith 1998 
 */ 

#include "defs.h"

#include FIREBALL_HEADER

inherit "/std/room"; 

void
create_room()
{
   set_short("North Goal Net"); 
   set_long("Fireball north goal net. This is where the ball rolls " +
            "when a goal is scored. No players should ever be able " +
            "to enter here.\n"); 
   add_exit(FIREBALL_ARENA+"ar_6_11", "south"); 
}
