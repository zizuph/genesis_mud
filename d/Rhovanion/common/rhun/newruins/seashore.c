
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"

create_room()
{
set_short("Seashore");
set_long("You stand on a sandy beach on the"
	+" east side of the vast Sea of Rhun.  Off to the northeast, you"
	+" can view a forest of tall, dark trees with a thick covering"
	+" of heavy green leaves. The seashore continues to the south"
	+" from here, while the walls of the ruined fort lie to the east.\n");

add_exit(RHUN_DIR+"newruins/seashor2","south",0);
add_exit(RHUN_DIR+"newruins/seapath","east",0);

add_item(({"sea","Sea","Sea of Rhun","water"}),"The"
	+" Sea of Rhun lies just to the west. It stretches on seemingly"
	+"forever.\n");
add_item(({"forest","trees","tree","leaves","leaf"}),"The"
	+" forest lies far off to the northeast.  It is impossible"
	+" to tell any further details from this distance.\n");

add_prop(ROOM_I_LIGHT,1);

}
