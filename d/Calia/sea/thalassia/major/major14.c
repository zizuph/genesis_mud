
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
        "the north, northeast, east and southeast. Surrounding "+
        "you on the southwestern side you see the bronze wall that "+
        "encompasses the entire Major Zone. It shines brightly in "+
        "the light giving everything around an almost bronze tint. "+
        "There is a building to the west with a sign beside the door.\n");

    add_item("sign","The sign reads 'Post Office'.\n");

    add_item("door","The door to the building is open. There is a sign "+
        "beside the door.\n");

    add_item("building","The building is carved right out of the "+
        "bronze wall to the west of you. There is a sign beside the "+
        "door.\n");

    add_item(({"wall","bronze wall","southwest","south",
        "southwest wall","south wall"}),"This shiny "+
        "metal surrounds the wall that encompasses the entire Major "+
        "Zone, except where the bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the north, northeast, east "+
        "and southeast.\n");

    add_swim_exit(THALM+"major16","north",0,1);
    add_swim_exit(THALM+"post","west",0,1);
    add_swim_exit(THALM+"major17","northeast",0,1);
    add_swim_exit(THALM+"major15","east",0,1);
    add_swim_exit(THALM+"major13","southeast",0,1);
}

int
do_read(string str)
{
    notify_fail("Read what? The sign?\n");

    if (!str || (str != "sign"))
        return 0;

    write("The sign reads: 'Post Office'\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_read,"read");
}
