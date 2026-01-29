
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
    set_short("Room with a fountain");
    set_long("This room has the fountain in it.\n");
    add_exit(CAVE+"water/room1","south");
}

