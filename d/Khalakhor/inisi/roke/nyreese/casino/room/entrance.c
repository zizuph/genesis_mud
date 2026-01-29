 /*
  * Entrance to the new Cadu Casino
  */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
    
inherit "/std/room";

void
create_room()
{
    set_short("casino entrance");
    set_long("You're standing at the entrance to a large building.\n");

    // Fance enrance - red carpet, sign on roof with gnomes running around with torches 
    // behind signs of colored glass
    // Have a bouncer here? Huge boss with some nice eq?

    add_exit(CASINO + "room/hall", "east", 0, 0, 0);
}