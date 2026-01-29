inherit "/std/door.c";
#include "defs.h"

void
create_door()
{
    ::create_door();
    set_pass_command(({"south", "s"}));
    set_door_name(({"kitchen door", "door"}));
    set_other_room(CAVERNS_DIR+"kitchen");
    set_open(0);
    set_pick(35);
}
