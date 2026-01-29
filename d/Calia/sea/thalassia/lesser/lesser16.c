
/* 	Lesser Zone of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define FISH 10


inherit "/d/Calia/std/water_room";
object *fish = allocate(FISH);

void
make_fish(int i)
{
    fish[i] = clone_object(SEA_CREATURES+"thalassian_fish");
    fish[i]->move(TO);
    tell_room(TO, QCTNAME(fish[i]) + " swims around.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < FISH; i++)
    {
        if (!fish[i])
            set_alarm(0.5, 0.0, &make_fish(i));
    }
}

void
create_water_room()
{
    set_short("Lesser Zone of Thalassia");
    set_long("You are swimming around in the Lesser Zone of "+
        "Thalassia. This is the second largest area of the "+
        "entire city and is almost entirely decorated with "+
        "white marble and silver. There are roads leading off to "+
        "the northeast and southwest. Surrounding "+
        "you on the northern side you see the silver wall that "+
        "encompasses the entire Lesser Zone. It shines brightly "+
        "in the light making everything around it almost glow.\n");

    add_item(({"wall","silver wall","northwest","northeast",
        "northwest wall","northeast wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Lesser Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northeast and southwest.\n");

    add_swim_exit(THALL+"lesser17","northeast",0,1);
    add_swim_exit(THALL+"lesser15","southwest",0,1);
    set_alarm(1.0,0.0,"reset_room");
}

public int
clean_up()
{
    int i;

    for (i=0; i < FISH; i++)
    {
        if (fish[i])
            return 1;
    }

    remove_object();
}
