
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
    set_long("You are in the entrance to the guard barracks. Here "+
        "is where all of the off-duty guards come to rest and relax "+
        "from the pressures of their job. There is a hallway that "+
        "leads off to the east and there branches to the north and "+
        "south. To the west lies the Lesser Zone of the city.\n");
    
    add_item("hallway", "The hallway leads to the east and then "+
        "becomes a T-intersection with branches leading to the "+
        "north and south.\n");

    add_swim_exit(THALL+"lesser26","west",0,1);
    add_swim_exit(THALL+"barrack_e_2","east",0,1);
}
