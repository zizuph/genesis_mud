inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos with header from Aldarion */
/* lowered the str required to open to 100 from 130. Damaris 11/2006 */
public void
create_door()
{
    set_door_id("isdoor");
    set_pass_command(({"w","west"}));
    set_door_name(({"gigantic platinum door","platinum door","door","gigantic door"}));
    set_other_room("/d/Kalad/common/caravan/company/s82");
    set_fail_pass("The door is closed, maybe you should open it?\n");
    set_open(0);
    set_str(100);
}
