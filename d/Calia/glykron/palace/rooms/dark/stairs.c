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
    object this;

    this = THIS;
    kroug[i] = clone_object(MONSTER("kroug_guardian"));
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

int 
blocked()
{
    object tp;

    tp = TP;
    if (member_array(tp->query_name(), ({ "Glykron", "Glykronjr", "Maniac" }) )
	!= -1)
    {
	write("You entered the dark shaft.\n");
	say(QCTNAME(tp) + " entered the dark shaft.\n");
	return 0;
    }

    write("The spiral staircase is under construction.\n");
    return 1;
}

void
create_room()
{
    set_short("Central Stairs");
    set_long(
        "This is a large octogonal-shaped room.  " +
        "A spiral staircase ascends upward, in the center of which is " +
        "projected a shaft of complete darkness, which seems impenetrable to " +
        "the light from below.  " +
        "A stair in the shape of a huge, wide gear rises from a recess in " +
        "the floor.  " +
        "The dimness of this room is tainted by the light from below.  " +
        "\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("dark_hall"), "south", 0);
    add_exit(ROOM("dark_gold"), "north", 0);
    add_exit(ROOM("dark_training"), "west", 0);
    add_exit(ROOM("dark_darkroom"), "east", 0);
    add_exit(ROOM("dark_stairs2"), "up", "@@blocked");
    add_exit(ROOM("gear"), "down", 0);
    add_item( ({ "staircase", "stair", "stairs" }), "It is made of crystal.\n");
    add_item("gear", "It looks like it might be part of a clock.\n");
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