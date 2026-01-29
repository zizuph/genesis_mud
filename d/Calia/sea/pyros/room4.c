
 /* Digit 03 FEB 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Calia/mountain/defs.h"


void
create_room()
{
    set_short("In a dark tunnel");
#include "desc1.h"

    add_exit(CAVE+"room1","west");
    add_exit(CAVE+"room38","east");
}
