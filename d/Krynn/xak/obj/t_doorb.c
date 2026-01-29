/* A door for the temple entrance in xak coded by Percy */

#include "/d/Krynn/xak/xlocal.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("t_door");
    set_pass_command(({"w", "west"}));
    set_door_name(({"metal door", "door", "doors", "double door", "double doors", "metal doors"}));
    set_other_room(TDIR + "outtemple.c");
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a small lock plated in platinum.\n");
    set_unlock_command("unlock");
    set_open(1);
    set_locked(0);
}
