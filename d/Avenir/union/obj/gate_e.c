/*
 * Revision:
 *   Lucius, May 2016: Code cleanups
 *
 */
inherit "/std/door";

#include <stdproperties.h>

#include "../defs.h"

public void
create_door(void)
{
    remove_name("door");
    set_door_name("gate");
    add_name("_union_gate");
    set_adj(({"heavy","thick","steel","black","massive"}));

    add_prop(OBJ_I_WEIGHT, 280000);
    add_prop(OBJ_I_VOLUME, 500000);
    add_prop(DOOR_I_HEIGHT, 500);
    add_prop(OBJ_M_NO_GET, 1);

    set_other_room(ROOM+"entry");
    set_door_id("_Union_entrance_gate");
    set_door_desc("This side of the gate is perfectly smooth "
      +"and flat, its dull black metal surface completely "
      +"unreflective. There is a small latch in the very centre "
      +"of the door.\n");
    set_open_desc("");
    set_closed_desc("");
    set_pass_command("west");
    set_fail_pass("The black steel gate is shut.\n");

    set_open_command(({"open","pull"}));
    set_open_mess(({"pulls on the massive steel gate.\nThe gate swings "
	+"open slowly on silent hinges.\n","The massive gate swings "
	+"open slowly.\n"}));
    set_fail_open(({"It is open already.\n","It does not move.\n"}));

    set_close_command(({"push","close"}));
    set_close_mess(({"pushes the massive steel gate closed.\nIt "
	+"swings shut with a resounding 'clang' that echos down the "
	+"hall.\n","The massive steel gate slowly closes.\nIt swings "
	+"shut with a resounding 'clang' that echos down the tunnel.\n"}));
    set_fail_close("It is closed already.\n");

    set_open(0);
    set_locked(1);

    set_lock_name("latch");
    set_lock_desc("The latch appears to be used to lock and "
      +"unlock the gate, as well as pull it open.\n");
    set_lock_command("lock");
    set_lock_mess(({"slides the latch on the massive steel gate.\n",
	"The black steel gate seems to shudder slightly.\n"}));
    set_fail_lock(({"It is locked already.\n","It must be closed first.\n"}));

    set_unlock_command(({"unlock","slide"}));
    set_unlock_mess(({"slides the latch on the massive steel gate.\n",
	"A strange noise comes from the black steel gate.\n"}));
    set_fail_unlock("It is unlocked already.\n");
}

public int
close_door(string arg)
{
    if (query_other_door()->query_broken())
	return NF("The gate cannot be closed in its current state.\n");

    return ::close_door(arg);
}
