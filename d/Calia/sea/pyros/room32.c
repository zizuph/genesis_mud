
 /* Digit 03 FEB 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Calia/mountain/defs.h"


void
create_room()
{
    set_short("In a dark tunnel");
    set_long("You have entered a thick white fog which seems to be "+
        "coming in from the east.  It is very cold here, so cold that "+
        "you can see your breath when you breathe.  The passage "+
        "continues off to the east and west.\n");

    add_item("fog","The fog seems to be cold to the touch, and gets "+
        "harder to see through to the east.\n");

    add_exit(CAVE+"room31","west");
    add_exit(CAVE+"room33","east");
}
