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
    set_pass_command(({"e","east"}));
    set_door_name(({"door","old door","solid door","old solid door"}));
    set_other_room(E_PATH + "treasure.c");
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

int
block(string str)
{
    object   tp = this_player();
    object   ghost;

    if (!present("ghost", environment(this_object())))
    {
	return 0;
    }
    else
    {
	write("A ghost blocks the door preventing you from passing.\n");
	ghost = present("ghost", environment(this_object()));
	ghost->attack_object(tp);
	tp->add_prop(I_ATTACKED_A_GHOST, 1);
	ghost->command("say to " + tp->query_name() + " You cannot pass!");
	
	return 1;
    }
}

void
init()
{
    ::init();

    add_action(block, "e");
    add_action(block, "east");
}
