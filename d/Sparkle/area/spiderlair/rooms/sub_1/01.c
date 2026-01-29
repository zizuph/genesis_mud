/*
 * /d/Sparkle/area/spiderlair/rooms/sub_1/01.c
 *
 * Sublevel 1 room in the spiderlair.
 *
 * Created February 2009, by Nerull.
 */

#include <stdproperties.h>
#include <macros.h>
#include "../../defs.h"

inherit ROOM_DIR + "room_std";

 
void
create_spider_hive()
{
    
    set_hive_level(1);  // Strenght and level of the hive.         
          
    set_name("In a corridor");
    add_name( ({ "room", "hall", "corridor" }) );

    set_short("Desc inc soon.");
    set_long("Desc inc soon.\n");
    
    add_item(({"wall", "walls"}),
     "soon to come.\n");

    add_exit(SUBLEVEL_1 + "02",   "north");
    
}



