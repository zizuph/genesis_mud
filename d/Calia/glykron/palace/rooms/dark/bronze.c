#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

object kroug = 0;

void
reset_room()
{
    if (kroug)
	return;

    kroug = clone_object(MONSTER("bronze_kroug"));
    kroug->move(THIS);
    tell_room(THIS, QCTNAME(kroug) + " arrives.\n");
}

void
create_room()
{
    set_short("The bronze room");
    set_long(break_string(
	 "This is a trapezoidal room whose west and south walls slant away "
	+"from you to the northeast.  "
	+"In the light of the torches you can see that the walls are bronze.  "
	+"Strangely, however, the bed is brass.  "
	+"\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("dark_gold"), "west", 0);
    add_exit(ROOM("dark_darkroom"),"south", 0);
    add_exit(ROOM("dark_sleepless"), "northeast", 0);
    add_item("bed","The brass bed has tattered bronze sheets.\n");
    call_out("reset_room", 1);
}
 
public int
clean_up()
{
    if (kroug)
        return 1;

    remove_object();
}