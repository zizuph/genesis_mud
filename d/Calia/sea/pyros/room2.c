
 /* Digit 15 MAY 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Calia/mountain/defs.h"


void
create_room()
{
    set_short("In a warm tunnel");
#include "smooth.h"

    add_exit(CAVE+"room5","west");
    add_exit(CAVE+"room1","east");
}
