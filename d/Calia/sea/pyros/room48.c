
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
    set_short("Travelling in a boiling river");
    set_long("The boiling river continues to flow here to the "+
        "south.  The upper walls and ceiling of the cavern are "+
        "covered in condensation and salt formations here.  "+
        "Steam rises from the river here, almost hot enough to "+
        "burn you.  The cavern continues north and south, and doesn't "+
        "appear to end in either direction soon.\n");
#include "river.h"

    add_exit(CAVE+"room49","north","@@water_walk");
    add_exit(CAVE+"room47","south","@@water_walk");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
