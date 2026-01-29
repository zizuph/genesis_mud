
/* 	Thalassian Guard Barracks

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
    set_short("Second floor of the guard tower");
    set_long("You are at the top of the stairs in the "+
        "second floor of the guard tower. Below you can "+
        "see the landing of the stairs on the first "+
        "floor. There is an exit to the south leading "+
        "into a small room.\n");
    add_item("stairs","They are stone stairs leading down "+
        "to the first floor of the guard tower.\n");
    add_item("first floor","You can't make out any details "+
        "about the area below.  Perhaps you should go down "+
        "and check it out.\n");
    add_swim_exit(THAL+"guard_sw_2_1","south",0,1);
    add_swim_exit(THAL+"guard_sw_1_3","down",0,1);
}




