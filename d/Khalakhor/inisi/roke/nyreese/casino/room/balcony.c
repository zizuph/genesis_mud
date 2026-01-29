 /*
  * Lounge room in the new Cadu Casino
  */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
      
inherit "/std/room";
  
void
create_room()
{
    set_short("upstairs balcony");
    set_long("You're standing on the grand balcony upstairs from the hall.\n");

    // Have a bar serving drinks?

    add_exit(CASINO + "room/stairs-n", "northwest"); 
    add_exit(CASINO + "room/stairs-s", "southwest");
    
}