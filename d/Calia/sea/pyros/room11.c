
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
#include "desc1.h"

    add_exit(CAVE+"room10","north");
    add_exit(CAVE+"room14","south");
    add_exit(CAVE+"room12","east");
}
