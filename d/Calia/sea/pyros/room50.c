
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
    set_short("A three-way intersection in a boiling river");
    set_long("You have come to a three-intersection in this boiling "+
       "river.  To the west you see a bright light far down the "+
       "tunnel.  North you can make out a bend in the passage towards "+
        "the east.  The upper walls and ceiling of the tunnel "+
        "are covered with salt formations.  The boiling river "+
        "flows southward from here.\n");
#include "river.h"

    add_exit(CAVE+"room51","north","@@water_walk");
    add_exit(CAVE+"room54","west","@@water_walk");
    add_exit(CAVE+"room49","south","@@water_walk");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
