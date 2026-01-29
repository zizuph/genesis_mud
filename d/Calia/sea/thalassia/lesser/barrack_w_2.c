
/* 	Guard Barracks in the Lesser Zone of Thalassia

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
    set_short("Guard barracks");
    set_long("You are in the middle of the guard barracks. Here "+
        "is where all of the off-duty guards come to rest and relax "+
        "from the pressures of their job. There is a hallway that "+
        "leads off to the north, east and south. To the west lies "+
        "a room that appears to hold weapons and armours.\n");

    add_item("hallway", "The hallway leads to the north, south and "+
        "east from here.\n");
    add_item("room", "The room to the west seems to contain both "+
        "weapons and armours. It is most likely a storage room of "+
        "some type.\n");

    add_swim_exit(THALL+"barrack_w_5","north",0,1);
    add_swim_exit(THALL+"barrack_w_3","west",0,1);
    add_swim_exit(THALL+"barrack_w_1","east",0,1);
    add_swim_exit(THALL+"barrack_w_8","south",0,1);
}
