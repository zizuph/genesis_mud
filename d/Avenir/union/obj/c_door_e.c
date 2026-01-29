/*
 * Revisions:
 *   Lucius, Apr 2016: Removed never used Elect code.
 *   Lucius, Jul 2017: Re-Code.
 */
#pragma strict_types

inherit "/std/door";
#include <stdproperties.h>

#include "../defs.h"

public void
create_door()
{
    remove_name("door");
    set_door_name("door");
    add_name("_union_door");
    set_adj(({"tall","pine"}));

    add_prop(OBJ_I_WEIGHT, 28000);
    add_prop(OBJ_I_VOLUME, 50000);
    add_prop(DOOR_I_HEIGHT, 350);
    add_prop(OBJ_M_NO_GET, "It is too big.\n");

    set_other_room(ROOM+"council");
    set_door_id("_council_entrance_door");
    set_door_desc("The face of the tall pine door is flat "+
	"and unadorned, made from solid and sturdy wood. A small latch "+
	"is fastened to this side of the door.\n");

    set_open(0);
    set_open_desc("A tall pine door stands open to the west.\n");
    set_closed_desc("A tall pine door stands closed to the west.\n");
    set_pass_command("west");
    set_fail_pass("The tall pine door is closed.\n");
    set_open_command(({"open","push"}));
    set_open_mess(({"pushes the tall door open.\n",
	"The tall pine door swings open.\n"}));
    set_fail_open(({"It is open already.\n","It is locked.\n"}));

    set_close_command(({"pull","close"}));
    set_close_mess(({"pulls the pine door shut.\n",
	"The tall pine door swings shut.\n"}));
    set_fail_close("It is closed already.\n");

    set_locked(1);
    set_lock_name("lock");
    set_lock_desc("It is a tiny indentation in the center of the door.\n");
    set_lock_command(({"lock"}));
    set_lock_mess(({"slides a tiny black sphere into the indentation "+
	    "of the door.\n", ""}));
    set_fail_lock(({"It is locked already.\n","It must be closed "+
	    "first.\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"locks the tall pine door with a tiny black "+
	    "sphere.\n", ""}));
    set_fail_unlock("It is unlocked already.\n");
    set_key(TOKEN_ID);
    set_pick(100);
}

public int
pass_door(string str)
{
    if (query_open() && !IS_ELDER(TP))
    {
	write("You are not permitted in there.\n");
	return 1;
    }

    return ::pass_door(str);
}

public int
close_door(string arg)
{
    int res = ::close_door(arg);

    if (res)
    {
	do_lock_door("");
	query_other_door()->do_lock_door(""); 
    }

    return res;
}

public int
lock_procedure(string str)
{
    int res = ::lock_procedure(str);

    if (res && !IS_ELDER(TP))
    {
	NF("It does not fit.\n");
	return 0;
    }

    return res;
}
