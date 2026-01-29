/*
 * outer_cell_1_door.c
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
    set_door_id("_macdunn_cell_1_door");
    set_other_room(ROOM + "jail_corridor_2");
    set_door_desc("The heavy cell door is made from thick " +
        "slabs of oak, bound together by heavy bands of " +
        "iron and rivets the size of your thumb.\n");
    set_door_name(({"door", "cell door", "oak door"}));
    set_open(0);
    set_locked(1);
    set_open_desc("A door stands open leading out of the cell " +
        "to the west.\n");
    set_open_mess(({"pushes the cell door open.\n",
        "Someone pushes the cell door open from the inside.\n"}));
    set_closed_desc("A closed door seals off the cell to " +
        "the west.\n");
    set_pass_command(({"w", "west"}));
    set_fail_pass("You're not likely to be able to walk " +
        "through a door. If you could you wouldn't need " +
        "one!\n");
    set_open_command(({"open", "push"}));
    set_fail_open(({"The cell door is already open.\n",
        "You try to open the cell door, but it's securely " +
        "locked.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the cell door closed.\n", 
        "The cell pulled shut by someone on the other " +
        "side.\n"}));
    set_fail_close("The door is already closed.\n");
}
    