
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
    set_short("In a warm tunnel");
#include "smooth.h"
    set_long("The walls of the tunnel are very smooth here, almost "+
        "as if they have been melted right out of the walls of this "+
        "volcano.  There is a rough passage leading off to the south.\n");

    add_exit(CAVE+"room17","west");
    add_exit(CAVE+"room10","south");
    add_exit(CAVE+"room8","east");
}
