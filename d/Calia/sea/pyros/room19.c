
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
    set_long("The walls here are unnaturally smooth, with an "+
        "almost glassy texture.  A warm wind blows in from the "+
        "south here.  There is a rough passage leading south.\n");

    add_exit(CAVE+"room18","east");
    add_exit(CAVE+"room20","south");
}
