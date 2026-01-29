inherit "/std/door";
#include "defs.h"

object
create_door()
{

    set_door_id("_castle_");
    set_pass_command(({"n", "north"}));
    set_door_name(({"wooden door","door"}));
    add_item(("wooden door", "door"}),
        "This is a magnificent mahoney wooden door. Intricate "+
        "carving cover it from top to bottom, showing elves "+
        "doing different activities like hunting and falconery.\n");
    set_open(2);
    set_other_room(VILLAGE + "/castle_path/castle_path07");
}
