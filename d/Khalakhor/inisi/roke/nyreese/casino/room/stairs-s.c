 /*
  * Southern staircase in the new Cadu Casino
  */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
      
inherit "/std/room";
  
void
create_room()
{
    set_short("southern staircase");
    set_long("You're standing midflight on the southern staircase between " +
             "the great hall, down below to the northwest, and a grand balcony " +
             "above to the northeast.\n");

    add_exit(CASINO + "room/hall", "northwest");
    add_exit(CASINO + "room/balcony", "northeast");
}