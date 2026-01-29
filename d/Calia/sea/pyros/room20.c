
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
#include "desc2.h"

    add_exit(CAVE+"room19","north");
    add_exit(CAVE+"room21","west");
}

void
init()
{
    ::init();
    add_action("do_collect","collect");
}
