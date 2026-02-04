inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("on ledge.");
    set_long(BSN(
	"You are on a narrow ledge chopped artifically far to the " +
        "right of the main line of acsent."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "hill_base", "east", 0);
    add_exit(TOMBDIR + "cottage_in", "enter", 0);
}


