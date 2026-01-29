#include "../local.h"


inherit SHIRE_DOOR;

void
create_shire_door()
{
    set_pass_command(({"d","down"}));

    set_door_name(({"steel grating","grating"}));

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_pass_command(({"u","up"}));
    set_other_room(CAVE_DIR + "d4");
    set_door_id("gcave_cell_no_2");
    set_open(1);    /*  1 if open, 0 if closed */
    set_locked(0);  /*  1 if locked, 0 if unlocked */
    set_pick(50);   /*  how hard is to pick lock  */

}
