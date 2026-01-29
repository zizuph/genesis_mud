#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit STDDOOR;

create_door()
{
    set_pass_command(({"n", "north"}));
    set_door_name(({"bronze door", "door", "north door"}));
    set_door_desc(BS("Is is a normal door made of solid bronze.", 70));
    set_other_room(PSLA+ "fine_tunnel06");
    set_open(0);
    set_open_desc("");
    set_closed_desc("");
}
