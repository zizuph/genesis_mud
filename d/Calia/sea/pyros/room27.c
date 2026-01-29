
 /* Digit 15 MAY 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"


void
create_room()
{
    set_short("In a warm tunnel");
    set_long("You have reached a corner in this tunnel that has been "+
        "quickly carved out of this volcano.  The tunnel leads off to "+
        "the south and east.  Rocks protrude from the walls here and "+
        "the walls are hot to the touch.  You can certainly tell you "+
        "are wandering inside a volcano.\n");

    add_exit(CAVE+"room26","south");
    add_exit(CAVE+"room28","east");
}

int
do_touch(string str)
{
    if (!str)
        return 0;

    if (str == "walls" || str == "wall")
    {
        write("Ouch!  The walls are very hot, causing you to scream out "+
            "in pain as you touch them.\n");
        TP->command("scream");
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action("do_touch","touch");
}
