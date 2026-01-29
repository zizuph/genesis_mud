
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
        "the north, east and northwest. To the west you see the "+
        "entrance to a grove of some sorts. Surrounding "+
        "you on the northeastern side you see the silver wall that "+
        "encompasses the entire Lesser Zone. It shines brightly "+
        "in the light making everything around it almost glow.\n");

    add_item("grove","The grove seems absolutely beautiful, "+
        "stretching out into the distance beyond what you can "+
        "see. Perhaps you could head to the west and take a "+
        "better look?\n");

    add_item(({"wall","silver wall","northeast",
        "northeast wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Lesser Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the north, east and northwest.\n");

    add_swim_exit(THALL+"lesser21","north",0,1);
    add_swim_exit(THALL+"lesser20","northwest",0,1);
    add_swim_exit(GROVE+"grove9","west",0,1);
    add_swim_exit(THALL+"lesser23","east",0,1);
}
