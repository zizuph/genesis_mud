inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos with header from Aldarion */
create_door()
{
    set_door_id("bdoor");
    set_pass_command(({"w","west"}));
    set_door_name(({"oak door","door"}));
    set_other_room("/d/Kalad/common/caravan/company/s36");
    set_fail_pass("The door is closed, maybe you should open it?\n");
    set_open(0);
}
