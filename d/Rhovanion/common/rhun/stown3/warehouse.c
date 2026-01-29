
#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Warehouse");
set_long(break_string("You have stepped into a very large, very empty"
	+" wooden warehouse.  There is nothing being stored here.  It's"
	+" apparently been a while since any deliveries were made.  The"
	+" only exit is back onto the street to the northeast."
	+"\n",75));

AE(RHUN+"stown3/south_road","northeast",0);

add_prop(ROOM_I_LIGHT,1);IN

}
