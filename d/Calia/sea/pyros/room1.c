
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
    set_short("A dark tunnel");
    set_long("You are standing in a dark tunnel inside the volcano "+
        "Mt. Pyros.  Tunnels lead off to the north, west and east, "+
        "and there is a small hole in the south wall which appears to "+
        "lead downwards into water.  You feel warm air blowing in from "+
        "the west.\n");

    add_exit(CAVE+"room2","west");
    add_exit(CAVE+"room3","north");
    add_exit(CAVE+"room4","east");
    add_exit(CAVE+"entrance","down");
}
