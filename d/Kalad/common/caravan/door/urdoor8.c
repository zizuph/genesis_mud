inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos with header from Aldarion */
create_door()
{
    set_door_id("urdoor8");
    set_pass_command(({"s","south"}));
    set_door_name(({"iron door","door","south door"}));
    set_other_room("/d/Kalad/common/caravan/lot/ur13");
    set_fail_pass("The door is closed, maybe you should open it?\n");
    set_open(0);
}
