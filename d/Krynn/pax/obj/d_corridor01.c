#include "../local.h"
inherit STDDOOR;

create_door()
{
    set_pass_command(({"n", "north"}));
    set_door_name(({"bronze door", "door"}));
    set_door_desc("The door is made of bronze and is now well-tarnished.\n");
    set_other_room(PSLA + "hall03");
    set_open(0);
    set_open_desc("");
    set_closed_desc("");
}
