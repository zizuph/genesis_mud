
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

#define NUM 3
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
    set_short("Stairs down");
    set_long("There are stairs here leading down to the "+
        "basement of the guard tower. South from here "+
        "you see the guard room, where the guards wait "+
        "for trouble to brew in the city.\n");
    add_item("stairs","The stairs are carved out of marble "+
        "and are quite finely crafted. They lead down into "+
        "the basement.\n");
    add_item("basement","You can just make out the landing "+
        "of the stairs below but do not see anything of "+
        "particular notice. Perhaps you should venture "+
        "down to see what is there.\n");
    add_item("guard room","There is a large guard room to the "+
        "south of here. In the middle of that room see what "+
        "looks like a table.\n");
    add_item("table","The table is in the guard room to the "+
        "south of here.\n");

    add_swim_exit(THAL+"guard_sw_1_2","south",0,1);
    add_swim_exit(THAL+"guard_sw_b_4","down",0,1);
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



