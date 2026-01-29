
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
    set_long("You are in the hallway in the guard barracks. Here "+
        "is where all of the off-duty guards come to rest and relax "+
        "from the pressures of their job. This hallway continues to "+
        "the north. To the west lies the pub, while to the east lies "+
        "one of the sleeping chambers.\n");

    add_item("hallway", "The hallway leads off to the north.\n");
    add_item("pub", "The pub lies off to the west. You could probably "+
        "find something there to eat and drink.\n");
    add_item(({"sleeping chamber", "sleeping chambers","chamber","chambers"}),
        "To the east lies one of the sleeping chambers here in the guard "+
        "barracks. The guards go there to sleep when they are not on duty.\n");

    add_swim_exit(THALL+"barrack_e_2","north",0,1);
    add_swim_exit(THALL+"barrack_e_6","east",0,1);
    add_swim_exit(THALL+"barrack_e_4","west",0,1);
}
