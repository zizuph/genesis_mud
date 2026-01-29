/* A door for the crypt entrance coded by Percy */

#include "../local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("d_hole1");
    set_pass_command(({"n", "north"}));
    set_door_name(({"marble door", "door", "doors", "double door",
	"double doors", "marble doors"}));
    set_other_room(TDIR + "crypt1");
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a small lock made out of what looks like black bone.\n");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
}
