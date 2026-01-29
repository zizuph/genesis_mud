#pragma strict_types
inherit "/std/door";

#include "../defs.h"
#include <stdproperties.h>

public void
create_door(void)
{
    set_door_name("door");
    add_name("_union_door");
    set_short("carved oaken door");
    set_adj(({"wooden","carved","oak","oaken","thick"}));

    add_prop(OBJ_I_WEIGHT, 28000);
    add_prop(OBJ_I_VOLUME, 50000);
    add_prop(DOOR_I_HEIGHT, 300);
    add_prop(OBJ_M_NO_GET, "It is too big.\n");

    set_other_room(ROOM + "library");
    set_door_id("_library_entrance_door");
    set_open(0);
    set_door_desc("A myriad of deep, bas-relief carvings cover "
      +"the surface of the door, of shields and waves and "
      +"intertwining laces. It is thick, and made from "
      +"solid and heavy oak.\n");
    set_open_desc("");    // Taken care of in the room desc
    set_closed_desc("");  // Taken care of in the room desc
    set_pass_command("east");
    set_fail_pass("The carved oaken door is closed.\n");
    set_open_command(({"open","pull"}));
    set_open_mess(({"pulls the carved oaken door open.\n",
	"The carved oaken door opens outwards.\n"}));
    set_fail_open(({"It is open already.\n","It does not move.\n"}));
    set_close_command(({"push","close"}));
    set_close_mess(({"pushes the oak door shut.\n",
	"The carved oaken door closes.\n"}));
    set_fail_close("It is closed already.\n");
    set_locked(1);
    set_lock_name("indentation");
    set_lock_desc("It is a shallow indentation, the shape of "
      +"a perfect half-sphere.\n");
    set_lock_command("lock");
    set_lock_mess(({"inserts a tiny black sphere into an indentation "
	+"in the carved oaken door.\nA tiny 'click' sounds from the door.\n",
	"You hear a tiny 'click' from the carved oaken door.\n"}));
    set_fail_lock(({"It is locked already.\n","It must be closed "
	+"first.\n"}));
    set_unlock_command(({"unlock","insert"}));
    set_unlock_mess(({"places a tiny black sphere in the "
	+"indentation in the carved oaken door.\n",
	"A tink 'click' sounds from the carved oaken door.\n"}));
    set_fail_unlock("It is unlocked already.\n");
    set_key(TOKEN_ID);
    set_pick(25);
}

public void
do_pick_lock(int skill, int pick)
{
    if (skill > pick)
    {
	write("You fiddle with the small indentation, and finally "+
	    "hear a small 'click' from the mechanism.\n");
	say("A small 'click' arises from the door.\n");
	do_unlock_door("");
	other_door->do_unlock_door(check_call(unlock_mess[1]));
    } 
    else if (skill < (pick - 50))
    {
	write("You cannot even determine how the lock works, "+
	    "let alone open it.\n");
    }
    else
    {
	write("You fiddle with the small indentation, but cannot "+
	    "seem to make it open.\n");
    }
}
