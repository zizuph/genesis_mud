
/* 	Cold Water Spring House in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

void
create_water_room()
{
    set_short("Inside the cold water spring house");
    set_long("You have entered the cold water spring house "+
        "of Thalassia. In the centre of the room you see "+
        "a silver well of sorts. Above the well there is a "+
        "basin with a large pipe on top of it running straight "+
        "up to the ceiling of the room. At the bottom of the "+
        "well is the magical cold water spring granted to the "+
        "citizens of Thalassia by Lord Diabrecho himself. This "+
        "spring supplies cold water for the entire city. To the "+
        "west you see a fountain and far to "+
        "the east you see the bridge tower.\n");

    add_item("fountain","To the west you see a large fountain.  "+
        "In the middle of the fountain you see statues made of "+
        "silver and gold. Perhaps you should swim that way if "+
        "you want to take a closer look at it.\n");

    add_item(({"spring","cold water spring","magical spring"}),
        "The spring is far down inside of the silver well. So "+
        "far in fact that you cannot see it, but you can definately "+
        "feel its effects when you put your hand above the well and "+
        "feel the cold water rising from it.\n");

    add_item("ceiling","The ceiling of this room is covered in "+
        "silver and has a solitary pipe running into it from the "+
        "top of the basin.\n");

    add_item("basin","This basin sits atop the well to collect the "+
        "cold water that comes from the spring. At the very top of "+
        "basin is a large pipe that runs to the ceiling.\n");

    add_item(({"pipe","large pipe"}),"This pipe collects the water "+
        "that gets trapped in the basin and transports it to where it "+
        "is needed in the entire city.\n");

    add_item(({"well","silver well"}),"This silver well is quite "+
        "deep, so deep you cannot see the bottom of it. When you "+
        "place your face over it to look down it, you notice that "+
        "the water coming out of it is quite cold and refreshing.\n");

    add_item(({"tower","bridge tower"}),"This three storey tower "+
        "is located directly in the centre of the bridge that "+
        "connects the citadel to the lesser zone.\n");

    add_swim_exit(THALC+"fountain","west",0,1);
    add_swim_exit(THALC+"citadel14","east",0,1);
}
