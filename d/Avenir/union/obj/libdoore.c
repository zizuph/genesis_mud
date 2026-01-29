#pragma strict_types
inherit "/std/door";

#include "../defs.h"
#include <stdproperties.h>

public void
create_door()
{
    set_door_name("door");
    add_name("_union_door");
    set_adj(({"wooden","carved","oak","oaken","thick"}));
    set_short("carved oaken door");

    add_prop(OBJ_I_WEIGHT, 28000);
    add_prop(OBJ_I_VOLUME, 50000);
    add_prop(DOOR_I_HEIGHT, 350);
    add_prop(OBJ_M_NO_GET, "It is too big.\n");

    set_other_room(HALL + "_ne3");
    set_door_id("_library_entrance_door");
    set_open(0);
    set_door_desc("The face of the thick oaken door is flat and "+
	"unadorned, made from solid and sturdy wood. A small latch "+
	"is fastened to this side of the door.\n");
    set_open_desc("");    // Taken care of in the room desc
    set_closed_desc("");  // Taken care of in the room desc
    set_pass_command("west");
    set_fail_pass("The carved oaken door is closed.\n");
    set_open_command(({"open","push"}));
    set_open_mess(({"pushes the carved oaken door open.\n",
	"The carved oaken door swings open.\n"}));
    set_fail_open(({"It is open already.\n","It does not move.\n"}));
    set_close_command(({"pull","close"}));
    set_close_mess(({"pulls the oak door shut.\n",
	"The carved oaken door swings shut.\n"}));
    set_fail_close("It is closed already.\n");
    set_locked(1);
    set_lock_name("latch");
    set_lock_desc("The latch is a simple, small sliding "
      +"mechanism that does not require a key.\n");
    set_lock_command(({"lock", "slide"}));
    set_lock_mess(({"slides the latch on the carved oaken door.\n", ""}));
    set_fail_lock(({"It is locked already.\n","It must be closed first.\n"}));
    set_unlock_command(({"unlock", "slide"}));

    set_unlock_mess(({"slides the latch on the carved oaken door open.\n",
	""}));
    set_fail_unlock("It is unlocked already.\n");
    //  set_key("");
    set_pick(5); // Easy to pick, since it does not need a key
}

public void
do_pick_lock(int skill, int pick)
{
    if (skill > pick)
    {
	write("Your skill in picking locks allows you to detect the "+
	    "latch on the door, which you slide open.\n");
	do_unlock_door("");
	other_door->do_unlock_door(check_call(unlock_mess[1]));
    } 
    else ::do_pick_lock(skill, pick);
}
