
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
        "leads off to the north, west and south. To the east lies "+
        "a room that appears to hold weapons and armours.\n");

    add_item("hallway", "The hallway leads to the north, south and "+
        "west from here.\n");
    add_item("room", "The room to the east seems to contain both "+
        "weapons and armours. It is most likely a storage room of "+
        "some type.\n");

    add_swim_exit(THALL+"barrack_e_8","north",0,1);
    add_swim_exit(THALL+"barrack_e_1","west",0,1);
    add_swim_exit(THALL+"barrack_e_3","east",0,1);
    add_swim_exit(THALL+"barrack_e_5","south",0,1);
}
