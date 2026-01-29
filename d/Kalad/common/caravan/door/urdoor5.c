inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos with header from Aldarion */
create_door()
{
    set_door_id("urdoor4");
    set_pass_command(({"n","north"}));
    set_door_name(({"iron door","door","north door"}));
    set_other_room("/d/Kalad/common/caravan/lot/ur11");
    set_fail_pass("The door is closed, maybe you should open it?\n");
    set_open(0);
}
