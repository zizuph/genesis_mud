
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
    guard[i] = clone_object(SEA_CREATURES+"ori_triton");
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
    set_short("Guard barracks sleeping chamber");
    set_long("This is one of the sleeping chambers of the guard "+
        "barracks. Lining the walls you see beds for the guards "+
        "to sleep on when they are not on duty patrolling the "+
        "streets of this city. The hallway lies off to the west.\n");

    add_item(({"bed", "beds"}), "The beds line the walls of this "+
        "room on all sides. They are made of a heavy stone material "+
        "and covered with a mattress, blankets and a pillow.\n");
    add_item(({"blanket", "blankets"}), "The blankets are made of a "+
        "heavy fur from some type of land dwelling creature.\n");
    add_item(({"pillow", "pillows"}), "The pillows are made from "+
        "some type of thin cloth stuffed with what appears to be "+
        "seaweed. They are actually quite comfortable to the touch.\n");
    add_item(({"mattress", "mattresses"}), "The mattresses are made out "+
        "of a heavier cloth material than the pillows, but are stuffed "+
        "with the same type of seaweed inside. They are firm, but quite "+
        "comfortable to the touch.\n");
    add_item("hallway", "The hallway lies back to the west.\n");

    add_swim_exit(THALL+"barrack_e_5","west",0,1);
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
