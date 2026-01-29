
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
    set_short("Guard tower basement stairs");
    set_long("You are at the bottom of the stairs in the "+
        "basement of the guard tower. Above you can "+
        "see the landing of the stairs on the first "+
        "floor. There is an exit to the south leading "+
        "into a small room.\n");
    add_item("stairs","They are stone stairs leading up "+
        "to the first floor of the guard tower.\n");
    add_item("first floor","You can't make out any details "+
        "about the area below.  Perhaps you should go up "+
        "and check it out.\n");
    add_swim_exit(THAL+"guard_se_b_1","south",0,1);
    add_swim_exit(THAL+"guard_se_1_3","up",0,1);
}

