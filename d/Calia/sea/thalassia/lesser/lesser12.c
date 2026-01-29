
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

inherit "/d/Calia/std/water_room";


void
create_water_room()
{
    set_short("Lesser Zone of Thalassia");
    set_long("You are swimming around in the Lesser Zone of "+
        "Thalassia. This is the second largest area of the "+
        "entire city and is almost entirely decorated with "+
        "white marble and silver. There are roads leading off to "+
        "the north, northeast, east, southeast and south. To the "+
        "west you see the bridge leading out of the Lesser Zone "+
        "and into the Major Zone of the city. Above the bridge "+
        "looms the guard tower. Northwest and southwest you see "+
        "the silver wall that surrounds the entire Lesser Zone. It "+
        "shines brightly in the light making everything around "+
        "it almost glow.\n");

    add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the west into the Major Zone of the city. On the top "+
        "of the bridge sits the three storey guard tower.\n");

    add_item(({"wall","silver wall","northwest","southwest",
        "northwest wall","southwest wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Lesser Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the north, northeast, east, southeast "+
        "and south.\n");

    add_swim_exit(THALL+"lesser13","north",0,1);
    add_swim_exit(THALL+"brguard_w_1_1","west",0,1);
    add_swim_exit(GROVE+"grove5","east",0,1);
    add_swim_exit(THALL+"lesser10","south",0,1);
    add_swim_exit(THALL+"lesser14","northeast",0,1);
    add_swim_exit(THALL+"lesser11","southeast",0,1);
}
