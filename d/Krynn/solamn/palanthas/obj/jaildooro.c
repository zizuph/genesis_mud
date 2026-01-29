/* created by Aridor 06/19/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("jdoor");
    set_pass_command(({"s","south","enter","go through","in"}));
    set_door_name(({"iron bars","bars"}));
    set_door_desc("Very strong iron bars.\n");
    set_closed_desc("There are closed iron bars leading south.\n");
    set_open_desc("There are open iron bars leading south.\n");
    /*set_open_mess("opens the iron bars","The iron bars open.");
    set_close_mess("closes the iron bars.","The iron bars close.");*/
    set_fail_open(({"The iron bars are already open.\n","The iron bars are locked.\n"}));
    set_fail_close("The iron bars are already closed.\n");
    set_fail_lock(({"They are already locked.\n","You must close the iron bars first.\n"}));
    set_fail_unlock("The iron bars are already unlocked.\n");
    set_fail_pass("The iron bars are closed.\n");
    set_lock_desc("The lock is very big and looks unbreakable.\n");
    set_key("the_key_from_the_future");
    set_other_room(ROOM + "jailcell");
    set_open(0);
    set_locked(1);
    set_unlock_command("unlock");
    set_lock_command("lock");
    set_lock_name("lock");
    set_pick(90);
}
