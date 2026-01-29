
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
#include "smooth1.h"

    add_exit(CAVE+"room26","north");
    add_exit(CAVE+"room7","west");
    add_exit(CAVE+"room5","east");
}
