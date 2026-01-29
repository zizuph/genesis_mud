
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Seashore");
set_long(break_string("You stand on a sandy beach on the"
	+" east side of the vast Sea of Rhun.  Off to the northeast, you"
	+" can view a forest of tall, dark trees with a thick covering"
	+" of heavy green leaves.  The seashore continues to the"
	+" north"
	+" from here, while the outskirts of some old ruins lie to the east."
     +"\n",75));

AE(RHUN+"ruins/seashore2","north",0);
AE(RHUN+"ruins/sw_side","east",0);

add_item(({"sea","Sea","Sea of Rhun","water"}),break_string("The"
	+" Sea of Rhun lies just to the west.  It stretches on seemingly"
	+"forever.\n",75));
add_item(({"forest","trees","tree","leaves","leaf"}),break_string("The"
	+" forest lies far off to the northeast.  It is impossible"
	+" to tell any further details from this distance.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
