
 /* Digit 03 FEB 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Calia/mountain/defs.h"

#define NUM 3
#define THIS this_object()
object this, *kroug = allocate(NUM);

void
make_monster(int i)
{
    kroug[i] = clone_object("/d/Calia/sea/creatures/medium_wkroug");
    kroug[i]->arm_me();
    kroug[i]->move(this);
    tell_room(this, QCTNAME(kroug[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < NUM; i++)
        if (!kroug[i])
            set_alarm(0.5, 0.0, &make_monster(i));
}

void
create_room()
{
    set_short("In a dark tunnel");
#include "desc1.h"

    add_exit(CAVE+"room34","north");
    add_exit(CAVE+"room1","south");
    this = THIS;
    set_alarm(1.0, 0.0, reset_room);
}

public int
clean_up()
{
    int i;

    for (i=0; i < NUM; i++)
        if (kroug[i])
            return 1;

    remove_object();
}
