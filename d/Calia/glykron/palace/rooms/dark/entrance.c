#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define NUM 4
object *kroug = allocate(NUM);

void
make_monster(int i)
{
    kroug[i] = clone_object(MONSTER("very_young_kroug"));
    kroug[i]->move(this_object());
    tell_room(this_object(), QCTNAME(kroug[i]) + " arrives.\n");
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
init()
{
    ::init();
    add_action("open", "open");
    add_action("unlock", "unlock");
}

int
open(string str)
{
    if (str != "door" && str != "doors")
	return 0;
    write("The doors are permanently locked.\n");
    return 1;
}

int
unlock(string str)
{
    if (str != "door" && str != "doors")
	return 0;
    write("The doors cannot be unlocked.\n");
    return 1;
}
    
void
create_room()
{
    set_short("Dark palace entrance");
    set_long(
	"This is a large trapezoidal-shaped room whose east and west walls " +
	"slope away from you to the south.  " +
	"The room is very dim.  " +
	"\n" +
	"There are crystalline double doors leading south which are closed.\n"
    );
    add_item( ({ "door", "doors" }), "The doors are permanently locked.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("dark_hall"), "north", 0);
    add_exit(ROOM("dark_shop"), "east", 0);
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