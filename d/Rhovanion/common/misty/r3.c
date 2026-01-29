/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "climb.h"

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("small cave");
    set_long(BS("Another cave room. This one is very small and not "+
                "particularly interesting. It is so small that you can "+
                "hardy turn here.\n"));


    add_exit(MISTY_DIR+"r2", "up");

}
