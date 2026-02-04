inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("cavern entrance.");
    set_long(BSN(
	"Straight ahead and just outside the cemetary rises a sheer " +
        "perpendicular cliff at whose base an immense forboding " +
        "cavern lies."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "cavern", "in", 0);
}


