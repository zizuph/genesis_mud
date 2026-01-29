
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

inherit "/d/Calia/std/water_room";


void
create_water_room()
{
    set_short("Major Zone of Thalassia");
    set_long("You are swimming around in the Major Zone of "+
        "Thalassia. This is the largest area of the "+
        "entire city and is almost entirely decorated with "+
        "white marble and bronze. There are roads leading off to "+
        "the north, east, northeast, south and southeast. To the "+
        "west you see the bridge leading out of the Major Zone "+
        "and into the Lesser Zone of the city. Above the bridge "+
        "looms the guard tower. Northwest and southwest you see "+
        "the bronze wall that surrounds the entire Major Zone. It "+
        "shines brightly in the light giving everything around "+
        "an almost bronze tint.\n");

      add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the west into the entrance area of the city. On the top "+
        "of the bridge sits the three storey guard tower.\n");

    add_item(({"wall","bronze wall","northwest","southwest",
        "northwest wall","southwest wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Major Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the north, northeast, east, "+
        "southeast and south.\n");

    add_swim_exit(THALM+"major38","north",0,1);
    add_swim_exit(THALM+"major39","northeast",0,1);
    add_swim_exit(THALL+"brguard_e_1_1","west",0,1);
    add_swim_exit(THALM+"major41","east",0,1);
    add_swim_exit(THALM+"major42","south",0,1);
    add_swim_exit(THALM+"major43","southeast",0,1);
}
