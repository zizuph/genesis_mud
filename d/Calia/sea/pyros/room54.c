
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
    set_short("An east/west passage in a boiling river");
    set_long("You see land to the west of here and think to "+
       "yourself that you may want to give your poor feet a "+
       "rest from this horrible river.  Farther to the west you "+
        "can make out a bright globe of light.  The upper walls "+
        "and ceiling here are covered in condensation and salt "+
        "formations.  The river flows off to the east.\n");
#include "river.h"

    add_exit(CAVE+"room55","west");
    add_exit(CAVE+"room50","east","@@water_walk");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}
