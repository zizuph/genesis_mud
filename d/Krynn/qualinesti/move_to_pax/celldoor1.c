
inherit "/std/door";

#include "../local.h"

create_door()
{
    set_door_id("celldoor");
    set_pass_command(({ "w", "west" }));
    set_door_desc("These are strong oaken door, reinforced by steel bars.\n");
    set_door_name(({ "door", "wooden door" }));
    set_other_room("/d/Krynn/qualinesti/move_to_pax/guard_room");
    
    set_open(0);
}
