#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define NUM 2
object *kroug = allocate(NUM);

void
make_monster(int i)
{
    kroug[i] = clone_object(MONSTER("kroug_in_training"));
    kroug[i]->move(THIS);
    tell_room(THIS, QCTNAME(kroug[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for(i = 0; i < NUM; i++)
	if(!kroug[i])
	    call_out("make_monster", 1, i);
}

void
create_room()
{
    set_short("The training room");
    set_long(break_string(
	"This is a small trapezoidal-shaped room whose north and south walls " +
	"slope away from you to the west.  " +
	"This room seems to be devoid of any furnishings but the walls are " +
	"marred in many places.  " +
	"\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("dark_stairs"), "east", 0);
    add_exit(ROOM("dark_lazy"), "west", 0);
    add_exit(ROOM("dark_silver"), "north", 0);
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