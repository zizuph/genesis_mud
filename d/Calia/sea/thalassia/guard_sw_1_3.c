
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
    set_short("Stairs up");
    set_long("There are stairs here leading up to the "+
        "second floor of the guard tower. South from here "+
        "you see the guard room, where the guards wait "+
        "for trouble to brew in the city. On the floor "+
        "you notice some type of hatch.\n");
    add_item("hatch","This hatch appears to lead to a room "+
        "directly below here. You cannot see any visible "+
        "latch or any way to open this hatch from this side.\n");
    add_item("stairs","The stairs are carved out of marble "+
        "and are quite finely crafted. They lead up to "+
        "the second floor.\n");
    add_item("second floor","You can just make out the landing "+
        "of the stairs above but do not see anything of "+
        "particular notice. Perhaps you should venture "+
        "up to see what is there.\n");
    add_item("guard room","There is a large guard room to the "+
        "south of here. In the middle of that room see what "+
        "looks like a table.\n");
    add_item("table","The table is in the guard room to the "+
        "south of here.\n");

    add_swim_exit(THAL+"guard_sw_1_1","south",0,1);
    add_swim_exit(THAL+"guard_sw_2_3","up",0,1);
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
void
init()
{
    ::init();
    add_action("open_hatch","open");
}

int
open_hatch(string str)
{
    notify_fail("Open what? The hatch?\n");
    if (str == "hatch")
    {
        write("Try as you might, you cannot seem to open "+
            "hatch from this side. Perhaps it only opens "+
            "from the other side?\n");
        tell_room(environment(TP), QCTNAME(TP) +
            " attempts to open the hatch on the floor but "+
            "fails.", TP);
        return 1;
    }
    return 0;
}



