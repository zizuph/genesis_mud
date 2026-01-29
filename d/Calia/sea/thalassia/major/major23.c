
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
        "the northeast, southeast and southwest. Surrounding "+
        "you on the northwestern side you see the bronze wall that "+
        "encompasses the entire Major Zone. It shines brightly in "+
        "the light giving everything around an almost bronze tint.\n");

    add_item(({"wall","bronze wall","northwest","north",
        "northwest wall","north wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Major Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northeast, southeast "+
        "and southwest.\n");

    add_swim_exit(THALM+"major24","northeast",0,1);
    add_swim_exit(THALM+"mural8","southeast",0,1);
    add_swim_exit(THALM+"major22","southwest",0,1);
}
