#pragma strict_types

#include <macros.h>
#include "../defs.h"

inherit TEMPLE + "std_cell.c";

#define NUM (2 + random(2))

object *slaves = allocate(NUM);

void
reset_temple_room()
{
    int x;

    for (x = 0 ; x < sizeof(slaves) ; x++)
    {
        if (!objectp(slaves[x]))
        {
            slaves[x] = clone_object(NNPC + "slave");
            slaves[x]->arm_me();
            slaves[x]->move(this_object());
        }
    }
}

void
create_temple_room()
{
    ::create_temple_room();

     set_short("small dark cell");
    set_long("You are standing in the confined quarters of a small cell " +
        "deep below the temple. The walls are bare and on the floor in " +
        "a corner is a bed of straw.\n");

    add_exit( DUNGTWO + "corr2.c", "east", "@@leave_cell", 0, 1);

    reset_temple_room();
}

mixed
leave_cell()
{
    write("You leave the cell and bolt the door behind you.\n");
    say(QCTNAME(this_player()) + " leaves the cell.\n");
    return 0;
}
