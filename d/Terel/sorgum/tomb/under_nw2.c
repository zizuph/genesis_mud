inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

object dweller1;
object dweller2;

init()
{
     ::init();
}

reset_room()
{
    if (!dweller1) {
        dweller1=clone_object(TOMBDIR + "dweller2");
        dweller1->move(this_object());
    }

    if (!dweller2) {
        dweller2=clone_object(TOMBDIR + "dweller2");
        dweller2->move(this_object());
    }

    if ((dweller1) && (dweller2))
        dweller1->team_join(dweller2);
}

void
create_room()
{
    set_short("Under the tomb");
    set_long(
        "You wonder how much longer you can stand it down here.  " +
	"The stench of decay nearly overpowers you.  The walls are beginning " +
	"to crumble here into a muck of wet sand, mortar and slimy grey " +
	"clay seeping from the cracks in the bricks that remain.\n"
    );

    add_prop(ROOM_I_INSIDE,1);
    add_exit(TOMBDIR + "under_nw3", "north", -5);
    add_exit(TOMBDIR + "under_nw", "south", -5);
    reset_room();
}
