
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
        "the northeast, east, southeast and south. Surrounding "+
        "you on the northwestern side you see the silver wall that "+
        "encompasses the entire Lesser Zone. It shines brightly "+
        "in the light making everything around it almost glow. "+
        "There is a building to the west with a sign beside the "+
        "door.\n");

    add_item("sign","The sign reads 'Guard Barracks'.\n");

    add_item("door","The door to the building is open. There is a sign "+
        "beside the door.\n");

    add_item("building","The building is carved right out of the "+
        "silver wall to the west of you. There is a sign beside the "+
        "door.\n");

    add_item(({"wall","silver wall","northwest",
        "northwest wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Lesser Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northeast, east, southeast and south.\n");

    add_swim_exit(THALL+"lesser15","northeast",0,1);
    add_swim_exit(THALL+"barrack_w_1","west",0,1);
    add_swim_exit(THALL+"lesser14","east",0,1);
    add_swim_exit(THALL+"lesser12","south",0,1);
    add_swim_exit(GROVE+"grove5","southeast",0,1);
}

int
do_read(string str)
{
    notify_fail("Read what? The sign?\n");

    if (!str || (str != "sign"))
        return 0;

    write("The sign reads: 'Guard Barracks'\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_read,"read");
}
