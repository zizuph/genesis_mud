
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Crossroads");
set_long(break_string("This is a small crossroads at the center of"
     +" this tiny town.  To the northwest lies a guard house, which"
     +" you might enter.  Two smaller buildings lie open to the"
     +" southeast and southwest, and a rough dirt road leads out"
     +" of town to the east.  Just northeast of this square lies"
     +" an old abandoned post office; it has been boarded up now, its"
     +" doors closed forever."
     +"\n",75));

AE(RHUN+"stown4/guard_house","northwest",0);
AE(RHUN+"stown4/empty_shack","southwest",0);
AE(RHUN+"stown4/wc_house","southeast",0);
AE(RHUN+"roads/section8/a","east",0);
AE(RHUN+"stown4/road_w","west",0);

add_item(({"building","buildings"}),break_string("Two small, wooden"
	+" buildings lie nearby, plus the larger guard house to the"
	+" northwest.  There is also a post office here, which was"
	+" long ago boarded up.\n",75));
add_item("guard house",break_string("The guard house is a large,"
	+" sturdy wooden building.  It appears you can step inside."
	+"\n",75));
add_item(({"po","post office","office"}),break_string("The post office"
	+" has been boarded up.  There is no entrance left leading"
	+" inside it.  You wonder if it was a place of great business,"
	+" so long ago.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
