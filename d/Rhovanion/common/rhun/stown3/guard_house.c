#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
#pragma save_binary

inherit RHUN + "stowns/guard_master";

create_room()
{
set_short("Guard house");
set_long(break_string("You are standing in the guardhouse near"
     +" the center of this small town.  It is made entirely"
     +" of wood, and is sparsely furnished.  Town guards apparently"
     +" spend their free time here.  The only exit from it"
     +" leads east, back out to the town's main street..\n",75));

AE(RHUN+"stown3/mid_road","east",0);

add_prop(ROOM_I_LIGHT,1);IN

    reset_room();
}
