
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
    set_short("Standing in a boiling river");
    set_long("You are walking in a boiling river which is flowing "+
        "eastwards.  It is quite shallow here, and you can see the "+
        "banks to the west.  Also to the west you see lights inside "+
        "what appears to be a chamber.  The upper walls and ceiling "+
        "here have salt formations and condensation on them.\n");

#include "river.h"

    add_exit(CAVE+"room59","west");
    add_exit(CAVE+"room57","east","@@water_walk");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
