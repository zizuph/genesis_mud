
/* 	Major Zone of Thalassia

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
    set_short("Major Zone of Thalassia");
    set_long("You are swimming around in the Major Zone of "+
        "Thalassia. This is the largest area of the "+
        "entire city and is almost entirely decorated with "+
        "white marble and bronze. There are roads leading off to "+
        "the west, east, southwest, south and southeast. To the "+
        "north you see the bridge leading out of the Major Zone "+
        "and into the Lesser Zone of the city. Above the bridge "+
        "looms the guard tower. Northwest and northeast you see "+
        "the bronze wall that surrounds the entire Major Zone. It "+
        "shines brightly in the light giving everything around "+
        "an almost bronze tint.\n");

      add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the north into the entrance area of the city. On the top "+
        "of the bridge sits the three storey guard tower.\n");

    add_item(({"wall","bronze wall","northwest","northeast",
        "northwest wall","northeast wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Major Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the west, east, southwest, "+
        "south and southeast.\n");

    add_swim_exit(THALL+"brguard_s_1_1","north",0,1);
    add_swim_exit(THALM+"major2","west",0,1);
    add_swim_exit(THALM+"major6","east",0,1);
    add_swim_exit(THALM+"major1","southwest",0,1);
    add_swim_exit(THALM+"major3","south",0,1);
    add_swim_exit(THALM+"major5","southeast",0,1);
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