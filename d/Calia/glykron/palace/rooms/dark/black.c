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

    kroug = clone_object(MONSTER("black_kroug"));
    kroug->move(THIS);
    tell_room(THIS, QCTNAME(kroug) + " arrives.\n");
}

void
create_room()
{
    set_short("The black room");
    set_long(break_string(
	"This is a large trapezoidal-shaped room whose east and west walls " +
	"slope away to the north.  " +
	"This room is lit only by your light source, and the walls of the " +
	"room are almost pitch black, although here and there are splotches " +
	"of dark green and blue.  " +
	"A bed with black covers is visible.  " +
	"\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 0);
    add_exit(ROOM("dark_gold"), "south", 0);
    add_item("bed", "The black satin bed looks very sinister.\n");
    call_out("reset_room", 1);
}


public int
clean_up()
{
    if (kroug)
        return 1;

    remove_object();
}