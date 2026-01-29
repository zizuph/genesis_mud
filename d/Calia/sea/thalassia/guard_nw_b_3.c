
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

object this, *hippocampus = allocate(NUM);

void
make_monster(int i)
{
    hippocampus[i] = clone_object("/d/Calia/sea/creatures/hippocampus");
    hippocampus[i]->equip_me();
    hippocampus[i]->move(this);
    tell_room(this, QCTNAME(hippocampus[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < NUM; i++)
        if (!hippocampus[i])
            set_alarm(0.5, 0.0, &make_monster(i));
}

void
create_water_room()
{
    set_short("Guard tower stables");
    set_long("You have entered the stables of this guard "+
        "house. Here you see the steeds these guards could "+
        "ride to pursue any would-be attackers of the city. "+
        "There is a hatch in the roof of this room that leads "+
        "up to the room above you, presumably so the mounted "+
        "guards would have quick access to the outside and "+
        "wouldn't have to ride up through the stairs.\n");
    add_item(({"hatch","roof hatch"}),"The hatch appears "+
        "to enter the room directly above this one so that "+
        "the mounted guards might chase their foes with "+
        "greater speed than if they had to go up the stairs. "+
        "It also appears that the hatch is one-way, meaning "+
        "you could not come back down through the hatch if "+
        "you entered it.\n");
    add_swim_exit(THAL+"guard_nw_b_1","south",0,1);
    this = THIS;
    set_alarm(1.0, 0.0, reset_room);
}

public int
clean_up()
{
    int i;

    for (i=0; i < NUM; i++)
        if (hippocampus[i])
            return 1;

    remove_object();
}

void
init()
{
    ::init();
    add_action("enter_hatch","enter");
}

int
enter_hatch(string str)
{
    notify_fail("Enter what? The hatch?\n");
    if (str == "hatch")
    {
        write("You swim up through the hatch.\n");
        tell_room(environment(TP), QCTNAME(TP) +
            " swims up through the hatch.\n", TP);
        this_player()->move_living("M",THAL+"guard_nw_1_3",0);
        tell_room(environment(TP), QCTNAME(TP) +
            " arrives through the hatch in the floor. The "+
            "hatch slams shut behind "+TP->query_objective()+
            ".\n", TP);
        return 1;
    }
    return 0;
}




