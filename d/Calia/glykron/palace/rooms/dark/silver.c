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

    kroug = clone_object(MONSTER("silver_kroug"));
    kroug->move(THIS);
    tell_room(THIS, QCTNAME(kroug) + " arrives.\n");
}

void
create_room()
{
    set_short("The silver room");
    set_long(break_string(
	"This is a trapezoidal room whose east and south walls slant away " +
	"from you to the northwest.  " +
	"The silver walls of the room are adorned with torches.  " +
	"There is a picture of an elven lady clothed in silver on the wall.  " +
	"A bed with silver sheets is here.  " +
	"\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("dark_gold"), "east", 0);
    add_exit(ROOM("dark_training"), "south", 0);
    add_exit(ROOM("dark_evil"), "northwest", 0);
    add_item(({"painting", "picture"}),
	"The picture appears to be of an elven lady, but it is quite " +
	"tattered.\n");
    add_item("bed","The silver bed looks very old.\n");
    call_out("reset_room", 1);
}

public int
clean_up()
{
    if (kroug)
        return 1;

    remove_object();
}