
 /* Digit 03 FEB 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"
#include "obsidian.h"


void
create_room()
{
    set_short("In a warm tunnel");
#include "desc3.h"

    add_item(({"small crevice","crevice"}),"The crevice appears to "+
       "lead downwards into some sort of room, but you can not make "+
       "out any details about it from here.  It also seems large enough "+
        "for you to climb down into.\n");

    add_exit(CAVE+"room23","east");
}

void
init()
{

    ::init();
    add_action("try_climb","climb");
    add_action("do_collect","collect");
}

int
try_climb(string str)
{
    notify_fail("Climb what?\n");

    if (!str || str !="down")
       return 0;


    TP->move_living("climbing down",CAVE+"room44",1);
    TP->add_fatigue(-5);
    return 1;
}
