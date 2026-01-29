#include "defs.h"
#include "/d/Emerald/telberin/defs.h"

inherit DOCK_PATH_ROOM;

public string    describe();

void
create_dock_path_room()
{
    object  obelisk;

    set_long(describe);
    add_exit("dock04", "east");
    add_exit("dock06", "west");
    add_door_exit(DOCK_DOOR_OBJ, "pav4", "north");

    obelisk = clone_object("/d/Emerald/docks/obj/obelisk");
    obelisk->set_no_show_composite(1);
    obelisk->move(this_object());
}


/*
 * Function name:        describe
 * Description  :        make some vamp-specific room text
 * Returns      :        the room description
 */
public string
describe()
{
    string  txt = "";

    if (this_player()->query_vampire())
    {
        txt = "Your preternatural eyes notice an obelisk beside the"
            + " path. Certainly any mortal would confuse it for a simple"
            + " boulder.";
    }

    return "A circular pathway leads around the small island, providing"
      + " access to the many docks.  Inside the circle, you can see a large"
      + " pavilion. " + txt + "\n\n";
} /* describe */
