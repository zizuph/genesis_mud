
/* 	Path To Thalassia 

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
    set_short("Tunnel to Thalassia");
    set_long("You are swimming through a tunnel leading "+
        "to the northwest and southeast. The tunnel walls "+
        "completely surround you on all sides. To the "+
        "northwest you see some buildings and beyond them "+
        "a vast city.\n");
    add_item(({"wall","walls","tunnel wall","tunnel walls"}),
        "These tunnel walls stretch right around you on "+
        "all sides. They appear to be made from some "+
        "type of marble bricks and are very precisely "+
        "fashioned and assembled. The tunnel forms a "+
        "passageway off to the northwest and southeast.\n");
    add_item(({"passage","passageway"}),"The passageway appears to "+
        "stretch out to the northwest for a while then curves gently "+
        "to the north while southeast the tunnel continues off into "+
        "the distance.\n");
    add_item(({"building","buildings"}),"The buildings seem to be "+
        "constructed from the same stone bricks that the walls are "+
        "made from.\n");
    add_item(({"city","vast city"}),"Details about the city are "+
        "hard to make out from this vantage point. It appears "+
        "to be quite large in size and formed of three seperate "+
        "rings, each inside of the other.\n");
    add_item(({"ring","rings","three rings","seperate rings",
        "three seperate rings"}),"These three rings form the "+
        "entire city, each ring even more beautiful than the "+
        "last.\n");

    add_swim_exit(THAL+"path3","northwest",0,1);
    add_swim_exit(THAL+"path1","southeast",0,1);
}
