/* Bupu's secret door in xak coded by Percy */

#include "/d/Krynn/xak/xlocal.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("bupudoor");
    set_pass_command(({"e", "east"}));
    set_door_name(({"stone door", "door", "secret door"}));
    set_other_room(CDIR + "southtmpl.c");
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a small lock made of stone to blend into the background.\n");
    set_unlock_command("unlock");
    set_open(1);
    set_locked(0);
}
