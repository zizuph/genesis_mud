
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
    set_long("You are walking in a boiling river.  To the east "+
        "lies the bank of the river, where you may want to cool "+
        "your feet.  The salt-encrusted walls and ceiling of the "+
        "cavern surround you, slightly shining with condensation.  "+
        "At the edge of the river, the bare basaltic rock is exposed, "+
        "dull and black.  The water causes your feet to hurt, but "+
        "if you are brave enough, or stupid enough, you may walk "+
        "farther in the river to the west.\n");

#include "river.h"
    add_exit(CAVE+"room46","west","@@water_walk");
    add_exit(CAVE+"room44","east");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
