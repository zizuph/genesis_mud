inherit "/std/door";

#include "../defs.h"
#include <stdproperties.h>

void
create_door()
{
    set_door_id("monastery_library_door");
    set_pass_command(({"n", "north", "enter"}));
    set_door_name(({"oak door","door"}));
    add_prop(DOOR_I_HEIGHT, 150);
    set_open(0);
    set_locked(1);
}
