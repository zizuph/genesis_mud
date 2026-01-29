
/* 	Thalassian Guard Barracks

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define NUM 5
#define THIS this_object()

inherit "/d/Calia/std/water_room";

object this, *guard = allocate(NUM);

void
make_monster(int i)
{
    guard[i] = clone_object("/d/Calia/sea/creatures/br_triton");
    guard[i]->equip_me();
    guard[i]->move(this);
    tell_room(this, QCTNAME(guard[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < NUM; i++)
        if (!guard[i])
            set_alarm(0.5, 0.0, &make_monster(i));
}

void
create_water_room()
{
    set_short("Thalassian guard house");
    set_long("This is the basement of a guardhouse in "+
        "the city of Thalassia. There is a large table "+
        "in this room. North of here you see stairs leading "+
        "up to the first floor. On the walls "+
        "you see racks for various kinds of weapons.\n");

    add_item(({"table","large table"}),"This table is made "+
        "of solid rock. It is most likely used by the guards "+
        "of this house when there is nothing to do but wait "+
        "for trouble to happen.\n");
    add_item("stairs","The stairs to the north lead up to "+
        "the first floor above.\n");
    add_item(({"upstairs","first floor"}),"You cannot make "+
        "any details out about the first floor.\n");
    add_item(({"wall","walls","rack","racks"}),"These racks "+
        "are designed to hold tridents and military forks. "+
        "They are all empty, presumably the guards have the "+
        "weapons from them.\n");

    add_swim_exit(THAL+"guard_ne_b_3","north",0,1);
    add_swim_exit(THAL+"guard_ne_b_2","west",0,1);
    this = THIS;
    set_alarm(1.0, 0.0, reset_room);
}

public int
clean_up()
{
    int i;

    for (i=0; i < NUM; i++)
        if (guard[i])
            return 1;

    remove_object();
}
