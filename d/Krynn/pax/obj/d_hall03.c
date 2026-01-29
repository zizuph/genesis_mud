#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit STDDOOR;

create_door()
{
    set_pass_command(({"s", "south"}));
    set_door_name(({"bronze door", "door"}));
    set_door_desc(BS("The door is made of bronze and it is now well-tarnished, " +
	"and covered with a relief drawing of Pax Tharkas.", 70));
    set_other_room(PSLA+ "corridor01");
    set_open(0);
    set_open_desc("");
    set_closed_desc("");
}
