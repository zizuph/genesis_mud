
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Town road");
set_long(break_string("You find yourself on a dirt road through town."
     +"  From here, it heads off to the northwest and south.  To the"
     +" east lies a small wooden house which you might enter."
     +"\n",75));

AE(RHUN+"stown6/crossroads","northwest",0);
AE(RHUN+"stown6/road_s","south",0);
AE(RHUN+"stown6/home_2","east",0);

add_prop(ROOM_I_LIGHT,1);

add_item(({"building","house"}),break_string("The small house"
     +" is made entirely of wood.  The entrance is apparently open.\n",75));

}

