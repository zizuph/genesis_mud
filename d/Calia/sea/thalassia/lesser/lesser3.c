
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
        "the northwest, north, northeast, west and east. To the "+
        "south you see the bridge leading out of the Lesser Zone "+
        "and into the Major Zone of the city. Above the bridge "+
        "looms the guard tower. To the east lies the Grandstand "+
        "of Thalassia. Southwest and southeast you see "+
        "the silver wall that surrounds the entire Lesser Zone. It "+
        "shines brightly in the light making everything around "+
        "it almost glow.\n");

    add_item(({"grandstand","Grandstand"}),"The Royal Grandstand "+
        "of Thalassia lies directly to the east of here. It rises "+
        "up into the waters above.\n");

    add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the south into the Major Zone of the city. On the top "+
        "of the bridge sits the three storey guard tower.\n");

    add_item(({"wall","silver wall","southwest","southeast",
        "southwest wall","southeast wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Lesser Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northwest, north, northeast, "+
        "west and east.\n");

    add_swim_exit(GROVE+"grove1","north",0,1);
    add_swim_exit(THALL+"lesser2","northwest",0,1);
    add_swim_exit(THALL+"lesser5","northeast",0,1);
    add_swim_exit(THALL+"lesser1","west",0,1);
    add_swim_exit(THALL+"grandstand1","east",0,1);
    add_swim_exit(THALL+"brguard_s_1_1","south",0,1);
}
