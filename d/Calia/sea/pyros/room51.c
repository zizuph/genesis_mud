
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
    set_short("The end of the boiling river");
    set_long("You have reached an endpoint of the boiling "+
        "river flowing out of the north wall.  An open area "+
        "of land lies to the east.  Your "+
        "feet cry out to you to give them some relief from this "+
        "hot water.  The water is quite shallow, and where it "+
        "touches and splashes the wall it reveals bare basalt.  "+
        "The upper walls and ceiling of the tunnel are covered "+
        "with salt formations however.  Brave souls can continue "+
        "southwards down the boiling river.\n");
#include "river.h"

    add_item(({"open area","land"}),"The land looks very dry "+
        "and very cool.  Your feet are crying out to you to "+
        "get some relief from this boiling water.\n");
    add_exit(CAVE+"room50","south","@@water_walk");
    add_exit(CAVE+"room52","east");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
