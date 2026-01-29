
 /* Jaacar 06 JUN 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"

void
create_room()
{
    set_short("In the Chamber of Psuchae");
    set_long("This is the Chamber of Psuchae.  This chamber "+
        "is very dimly lit.  The walls, or what you can see of them, are "+
        "covered in thousands of tiny shadows that do not appear to be "+
        "originating anywhere that you can see.  A fine mist floats "+
        "throughout the room, surrounding a statue of Psuchae.  You "+
        "can head back out to the shrine to the south.\n");

    add_item("statue","This statue is fairly large, but you cannot "+
        "really tell how big it is because the edges seem to expand "+
        "and contract on their own at random intervals.  The statue itself "+
        "is made from some sort of dark stone-like material that absorbs "+
        "almost all of the light in the room.  It depicts Psuchae "+
        "shrouded in its black cloak of shadow.  The eyes of the statue "+
        "are a deep piercing black and seem to be searching your soul.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_exit(WORSHIP_SHRINE+"common","south");
}
