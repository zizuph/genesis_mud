
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
    set_long("You are walking in a boiling river and have come "+
        "to a T-intersection.  Far to the west you see light, "+
        "while to the north the cavern continues on endlessly "+
        "into the darkness.  The river is flowing south from "+
        "here, flowing down the cavern leading south.  The "+
        "upper walls and ceiling are covered in condensation "+
        "from the steaming river, as well as salt formations.\n");
#include "river.h"

    add_exit(CAVE+"room57","west","@@water_walk");
    add_exit(CAVE+"room48","north","@@water_walk");
    add_exit(CAVE+"room46","south","@@water_walk");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
