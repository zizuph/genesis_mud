inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos with include borrowed from Aldarion */
create_door()
{
    set_door_id("idoor");
    set_pass_command(({"w","west"}));
    set_door_name(({"iron door","door"}));
    set_other_room("/d/Kalad/common/caravan/gateway/tower2a");
    set_fail_pass("The door is closed, maybe you should open it?\n");
    set_open(0);
}
