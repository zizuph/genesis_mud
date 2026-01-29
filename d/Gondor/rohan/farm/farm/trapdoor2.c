/* An example door made by Nick, 1991-12-19 */
/* used by Olorin to make door for          */
/* /d/Gondor/rohan/farm/road/yard1.c        */
/* Dec-1992                                 */


inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door() 
{
    ::create_door();
/* You need an id, and both sides should have the same id               */
    set_door_id("farm_stable_trapdoor");

    set_pass_command(({"u","up"}));

    set_door_name(({"trap door","hatch","door","trapdoor"}));
    set_door_desc("A simple plank covering a hole in the floor. The plank " +
        "looks quite heavy.\n");

    set_other_room(FARM_DIR + "farm/stable2");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);         /* 1 if open, 0 if closed */
    set_locked(1);       /* 1 if locked, 0 if unlocked */
    set_key("Stable_Trapdoor_Key");
}
