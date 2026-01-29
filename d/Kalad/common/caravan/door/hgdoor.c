inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_door()
{
    set_door_id("hgdoor");
    set_pass_command(({"n","north"}));
    set_door_name(({"pair of massive steel doors","massive steel doors","steel doors","doors","massive doors"}));
    set_other_room("/d/Kalad/common/wild/high/w1");
    set_fail_pass("The Highland Gate is closed!\n");
    set_open(0);
    set_str(500);
    set_door_desc("These huge double doors are the only way through the "+
      "huge encircling walls of Kabal. Built out of solid steel and "+
      "standing thirty feet in height, as well as several feet in "+
      "thickness, the Highland Gate is virtually impassable when closed. "+
      "A large winch lies beside the doors.\n");
}
