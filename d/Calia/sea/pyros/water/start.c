
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
    set_short("Wavewalkers start room");
    set_long("This is the Wavewalkers start room.\n");
    add_exit(CAVE+"water/room4","north");
    add_exit(CAVE+"water/room3","south");
}

