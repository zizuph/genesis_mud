
 /* Digit 03 FEB 95 */

inherit "/std/room";
inherit "/d/Calia/walkers/specials/water_walk";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"


void
create_room()
{
    set_short("On the edge of a boiling river");
    set_long("You are standing on the bank of a boiling river.  "+
       "It is moving very slowly and does not appear to be very "+
       "deep.  It flows off from here to the west.  You feel you "+
       "could probably walk on it, although you would endure some "+
       "pain in doing so.  This must be where the warm air was coming "+
       "from in the tunnels above.  You can climb back up from here "+
       "if you wish.\n");

    add_item(({"river","water","boiling river"}),"The water appears to be "+
        "about a hand-height deep and very hot judging from the amount "+
        "of steam rising up off of it.  You could probably walk in it "+
        "without too much fear of falling due to the current, but it "+
        "may cause you alot of pain because of the heat of the water.\n");

    add_item("steam","Wifts of steam are rising off of the river, making "+
        "this place very humid.\n");
    add_exit(CAVE+"room45","west","@@water_walk");
    add_exit(CAVE+"room24","up");

}
