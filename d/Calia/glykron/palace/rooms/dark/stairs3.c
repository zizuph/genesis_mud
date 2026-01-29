#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

/*
void
make_monster()
{
    object kroug;

    kroug = clone_object(MONSTER("stairs_kroug"));
    kroug->move(this_object());
    tell_room(this_object(), QCTNAME(kroug) + " arrives.\n");
}

void
reset_room()
{
    int i;

    if (present("kroug"))
	return;

    for (i = 0; i < NUM; i++)
	call_out("make_monster", 1);
}
*/

int
blocked()
{
    write("The spiral staircase is under construction.\n");
    return 1;
}

void
create_room()
{
    set_short("Central Stairs");
    set_long(break_string(
	"This is a large octogonal-shaped room.  " +
	"There is a landing of a spiral staircase, in the center of which is " +
	"projected a shaft of complete darkness, which seems impenetrable to " +
	"the light from below.  " +
	"A faint white light shines from below.  " +
	"\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("dark_hall"), "north", 0);
    add_exit(ROOM("dark_guard"), "south", 0);
    add_exit(ROOM("dark_stairs"), "up", "@@blocked");
    add_exit(ROOM("dark_stairs"), "down", 0);
    add_item(({"staircase", "stair", "stairs"}), "It is made of crystal.\n");
    add_item("gear", "It looks like it might be part of a clock.\n");
    call_out("reset_room", 1);
}