/* created by Aridor 06/19/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("jdoor");
    set_pass_command(({"s","south","out"}));
    set_door_name(({"iron bars","bars"}));
    set_door_desc("Very strong iron bars.\n");
    set_closed_desc("There are closed iron bars leading south.\n");
    set_open_desc("There are open iron bars leading south.\n");
    set_open_mess("opens the iron bars","The iron bars open.");
    set_close_mess("closes the iron bars.","The iron bars close.");
    set_lock_desc("You can't seem to find a lock.\n");
    //set_key(9684236);
    //set_unlock_command("unlock");
    //set_lock_command("lock");
    set_other_room(PALACE + "office15");
    set_open(0);
    set_locked(1);
    set_no_pick(1);
}

