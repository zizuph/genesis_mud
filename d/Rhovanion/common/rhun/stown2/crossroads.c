inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Crossroads");
set_long(break_string("This is a small crossroads at the northeast end of"
     +" town.  The dirt road continues on from northeast to southwest, with"
     +" a branch heading southeast through town.  Two buildings lie near"
     +" here: a large one to the northwest, and a smaller just to the"
     +" east."
     +"\n",75));

AE(RHUN+"stown2/guard_house","northwest",0);
AE(RHUN+"stown2/road_sw","southwest",0);
AE(RHUN+"stown2/road_ne","northeast",0);
AE(RHUN+"stown2/home_1","east",0);
AE(RHUN+"stown2/road_se","southeast",0);

add_item(({"building","buildings"}),break_string("The buildings are"
     +" made of wood, and appear open.  Why don't you"
     +" step inside?\n",75));

add_prop(ROOM_I_LIGHT,1);

}
