/*
 * Cave/dragon's lair
 * By Nerull, August 2009
 * 
 */

#include "defs.h"

inherit DRAGON_BASE;

string extra_line = "";

void
create_room()
{
    set_short("Inside a dark humid cave");
    set_long(dragon_lair_desc2(extra_line));

   
    reset_room();

    
    add_exit(DRAGON_DIR + "rooms/d3", "north");
    add_exit(DRAGON_DIR + "rooms/d1", "southeast");
    
}



public void
init()
{
    ::init();

}
void
reset_room()
{
}
