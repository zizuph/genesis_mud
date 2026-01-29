/*
 * g-07-inn-door.c
 * By Skippern
 */
#pragma save_binary
inherit "/std/door";

#include "../../defs.h"


public void
create_door()
{
    ::create_door();
    set_door_id("house-door-g08");
    set_pass_command(({"south"}));
    set_door_name(({"door","wooden door","large door","large wooden door"}));
    set_open_desc("A large wooden door leading south.\n");
    set_other_room(DOL_COMMON + "houses/g-08.c");
    set_door_desc("It is a large wooden door, it looks worn down.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(1);
    set_locked(0);
    set_pick(30);
    set_key("DolAmrothHouses");
    set_knock_command("knock");
}
