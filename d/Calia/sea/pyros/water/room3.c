
 /* Jaacar 03 JUNE 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"

void
create_room()
{
    set_short("Bottom of the fountain");
    set_long("This is the bottom of the fountain.\n");
    add_exit(CAVE+"water/room2","up");
    add_exit(CAVE+"water/start","north");
}

