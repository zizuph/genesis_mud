
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
    object weprack1, weprack2, armrack;

    set_short("Guard barracks storage room");
    set_long("You are in the armour and weapons storage room "+
        "of the guard barracks. Here you see an armour rack "+
        "as well as a couple of weapon racks around the room. "+
        "This is where the guards come to gather their weapons "+
        "and armours before heading off to their guard postings "+
        "around the city. There is a hallway back off to the "+
        "east.\n");

    weprack1 = clone_object(SEA_OBJECTS+"weapon_rack");
    weprack1->move(TO);
    weprack2 = clone_object(SEA_OBJECTS+"weapon_rack");
    weprack2->move(TO);
    armrack = clone_object(SEA_OBJECTS+"armour_rack");
    armrack->move(TO);

    add_swim_exit(THALL+"barrack_w_2","east",0,1);
}
