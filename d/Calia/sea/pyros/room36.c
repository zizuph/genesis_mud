
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
    set_long("You have reached a corner in this tunnel that has been "+
        "quickly carved out of this volcano.  The tunnel leads off to "+
        "the south and west.  Rocks protrude from the walls here and "+
        "the walls are hot to the touch.  You can certainly tell you "+
        "are wandering inside a volcano.\n");

    add_exit(CAVE+"room37","south");
    add_exit(CAVE+"room35","west");
}
