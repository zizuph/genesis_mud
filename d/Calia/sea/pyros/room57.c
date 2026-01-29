
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
    set_long("You are walking in a boiling river.  Far to the "+
        "west you can see some light.  The river also seems to "+
        "be a bit shallower here.  Perhaps there will be land to "+
        "the west where you can rest your burning feet.  The upper "+
        "walls and ceiling are coated with salt formations from the "+
        "river, but the lower walls are bare due to the moving water "+
        "splashing on them.\n");

#include "river.h"

    add_exit(CAVE+"room58","west","@@water_walk");
    add_exit(CAVE+"room47","east","@@water_walk");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
