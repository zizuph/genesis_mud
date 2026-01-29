 /*
  * Northern staircase in the new Cadu Casino
  */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
      
inherit "/std/room";
  
void
create_room()
{
    set_short("northern staircase");
    set_long("You're standing midflight on the northern staircase between " +
             "the great hall, down below to the southwest, and a grand balcony " +
             "above to the southeast.\n");

    add_exit(CASINO + "room/hall", "southwest");
    add_exit(CASINO + "room/balcony", "southeast");
}