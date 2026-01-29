inherit "/std/door";
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR MISTY_DIR + "gcaves/"

create_door()
{
    set_pass_command(({"d","down"}));

    set_door_name(({"steel grating","grating"}));

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_pass_command(({"d","down"}));
    set_other_room(CAVE_DIR + "d5");
    set_door_id("gcave_cell_no_1");
    set_open(0);    /*  1 if open, 0 if closed */
    set_locked(1);  /*  1 if locked, 0 if unlocked */
    set_pick(50);   /*  how hard is to pick lock  */

}
