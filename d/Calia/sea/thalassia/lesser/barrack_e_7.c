
/* 	Guard Barracks in the Lesser Zone of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define NUM 2

inherit "/d/Calia/std/water_room";

object *guard = allocate(NUM);

void
make_monster(int i)
{
    guard[i] = clone_object(SEA_CREATURES+"tin_triton");
    guard[i]->equip_me();
    guard[i]->move(TO);
    tell_room(TO, QCTNAME(guard[i]) + " arrives.\n");
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
    set_short("Guard barracks mess hall");
    set_long("You are in the mess hall of the guard barracks. "+
        "The off-duty guards come here to relax and eat their "+
        "meals and gossip about the daily activites of the "+
        "citizens and visitors to the city. You see several "+
        "tables and benches that the guards might could sit at "+
        "to eat. There is a hallway back to the east.\n");

    add_item("hallway", "There is a hallway back to the east.\n");
    add_item(({"table", "tables"}), "There are several tables here "+
        "that the guards might sit at to eat their meals. The "+
        "tables themselves are made from some type of very heavy "+
        "wood with stone-bottomed legs so that they do not float "+
        "away or move with the currents of the water.\n");
    add_item(({"bench", "benches"}), "There are several benches "+
        "here, one on each side of the tables. They are for the "+
        "guards of these barracks to sit on while eating their "+
        "meals. They are made from the same type of heavy wood "+
        "as the tables, and have the same stone-bottomed legs as "+
        "well so they do not float away or move with the currents "+
        "of the water.\n");

    add_swim_exit(THALL+"barrack_e_8","east",0,1);
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
