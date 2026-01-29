inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos with include borrowed from Aldarion */
create_door()
{
    set_door_id("wdoor");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door","door"}));
    set_other_room("/d/Kalad/common/caravan/slave/s6a");
    set_fail_pass("The door is closed, maybe you should open it?\n");
    set_open(0);
}
