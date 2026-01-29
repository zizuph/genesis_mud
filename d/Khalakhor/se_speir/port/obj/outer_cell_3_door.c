/*
 * outer_cell_3_door.c
 *
 * Doors for the jail cells in the prison.
 *
 * Khail - June 16/97
 */
#pragma strict_types

#include "defs.h"

inherit "/std/door";

public void
create_door()
{
    ::create_door();
    set_door_id("_macdunn_cell_3_door");
    set_other_room(ROOM + "jail_cell_3");
    set_door_desc("The heavy cell door is made from thick " +
        "slabs of oak, bound together by heavy bands of " +
        "iron and rivits the size of your thumb. The " +
        "whole thing is completed with a heavy lock " +
        "that should be able to resist any attempts to " +
        "break.\n");
    set_door_name(({"door", "cell door", "oak door",
        "west door", "west cell door"}));
    set_open(0);
    set_locked(1);
    set_open_desc("A door stands open leading into the cell " +
        "to the west.\n");
    set_closed_desc("A closed door seals off the cell to " +
        "the west.\n");
    set_pass_command(({"w", "west"}));
    set_fail_pass("You're not likely to be able to walk " +
        "through a door. If you could you wouldn't need " +
        "one!\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"pulls the cell door open.\n",
        "Someone pulls the cell door open from the outside.\n"}));
    set_fail_open(({"The cell door is already open.\n",
        "You try to open the cell door, but it's securely " +
        "locked.\n"}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the cell door closed.\n",
        "Someone pushes the cell door closed from the other " +
        "side.\n"}));
    set_fail_close("The door is already closed.\n");
    set_locked(0);
    set_lock_name("lock");
    set_lock_desc("The lock is a moderately intricate " +
        "drawbolt, that is locked into place by a heavy " +
        "set of tumblers.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the drawbolt closed with a " +
        "heavy clank.\n", "You hear the drawbolt lock into " +
        "place on the other side of the door with a heavy " +
        "clank.\n"}));
    set_fail_lock(({"The door is already locked.\n",
        "The door is open, locking it now is rather " +
        "pointless.\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the drawbolt and draws it " +
        "back.\n", "You hear the drawbolt unlock from the " +
        "other side with a loud clank and slide back.\n"}));
    set_fail_unlock("The cell door is already unlocked.\n");
    set_key(524523553); /* jailcell3 on a telephone *grin* */
    set_pick(60);
}
    