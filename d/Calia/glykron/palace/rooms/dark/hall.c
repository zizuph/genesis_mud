#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define NUM 3
object this, *kroug = allocate(NUM);

void
make_monster(int i)
{
    kroug[i] = clone_object(MONSTER("young_kroug"));
    kroug[i]->move(this);
    tell_room(this, QCTNAME(kroug[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i = 0; i < NUM; i++)
	if (!kroug[i])
	    call_out("make_monster", 1, i);
}

void
create_room()
{
    set_short("Hall");
    set_long(
	"This is a small trapezoidal-shaped room whose east and west walls " +
	"slope away from you to the south.  " +
	"This room is rather dim.  " +
	"Paintings adorn the east wall.  " +
	"\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("dark_entrance"), "south", 0);
    add_exit(ROOM("dark_stairs"), "north", 0);
    add_item(({"painting","paintings"}),
	"One of them is a picture of a charred wizard, with the name Kroug " +
	"below.\n");
    this = THIS;
    call_out("reset_room", 1);
}

public int
clean_up()
{
    int i;

    for (i = 0; i < NUM; i++)
        if (kroug[i])
            return 1;

    remove_object();
}