
 /* Digit 03 FEB 95 */

inherit "/std/room";
inherit "/d/Calia/walkers/specials/water_walk";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"
#include "salt.h"


void
create_room()
{
    set_short("In a boiling river");
    set_long("The cavern makes a bend here travelling north "+
        "as well as east.  The river seems to flow under the "+
        "south wall, but the space in which it does so is far "+
        "too small for you to look into.  The upper walls and "+
        "ceiling are covered in condensation and salt formations "+
        "from the boiling river.\n");

#include "river.h"

    add_exit(CAVE+"room47","north","@@water_walk");
    add_exit(CAVE+"room45","east","@@water_walk");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
