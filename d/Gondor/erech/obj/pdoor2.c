/*
 * pdoor1.c
 * By Skippern
 */
#pragma save_binary

#include "../erech.h"

inherit "/std/door";

public void
create_door()
{
    ::create_door();
    set_door_id("erechpath");
    set_pass_command(({"w","west"}));
    set_door_name(({"door","old door","solid door","old solid door"}));
    set_other_room(E_PATH + "central3.c");
    set_door_desc("The door is very solid, but there are several marks " +
		  "on it as if somebody have tried to break it open.\n");
    set_lock_command("lock");
    set_lock_name("padlock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_pick(35);
    set_key("ErechTunnelTreasury");
    set_knock_command("knock");
}
