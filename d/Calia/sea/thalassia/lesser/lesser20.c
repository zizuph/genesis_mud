
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
        "the west, east, southwest, southeast and south. To the "+
        "north you see the bridge leading out of the Lesser Zone "+
        "and into the Major Zone of the city. Above the bridge "+
        "looms the guard tower. Northwest and northeast you see "+
        "the silver wall that surrounds the entire Lesser Zone. It "+
        "shines brightly in the light making everything around "+
        "it almost glow.\n");

    add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the north into the Major Zone of the city. On the top "+
        "of the bridge sits the three storey guard tower.\n");

    add_item(({"wall","silver wall","northwest","northeast",
        "northwest wall","northeast wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Lesser Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the west, east, southwest, south "+
        "and southeast.\n");

    add_swim_exit(THALL+"brguard_n_1_1","north",0,1);
    add_swim_exit(THALL+"lesser18","west",0,1);
    add_swim_exit(THALL+"lesser21","east",0,1);
    add_swim_exit(THALL+"lesser19","southwest",0,1);
    add_swim_exit(GROVE+"grove9","south",0,1);
    add_swim_exit(THALL+"lesser22","southeast",0,1);
}
