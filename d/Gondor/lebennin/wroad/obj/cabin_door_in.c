#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"
#include <macros.h>

inherit "/std/door";

string query_closed();

void
create_door()
{
    set_other_room(AREA_DIR + "wroad/wr14");
    set_door_id("lebennin-cabin-door");
    set_door_name(({"pine door", "wood door", "door"}));
    set_door_desc("A solid @@query_closed@@ door made up of the same " +
        "material as the rest of the cabin. The door has an twisted branch " +
        "set a handle.\n");
    set_pass_command("out");
    add_item(({"branch", "handle"}), "A twisted gnarly pine branch serves " +
        "as the handle for the door.\n");

    /*
     * Need to pass empty strings to open/close desc to prevent the door
     * from generating room description
     */
    set_closed_desc("");
    set_open_desc("");

    set_open(0);
}

void
reset_door()
{
    other_door->reset_door();
}

string
query_closed()
{
    if (query_open())
        return "open";
    return "closed";
}
