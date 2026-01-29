#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
inherit RHUN_DIR + "stowns/guard_master.c";

create_room()
{
set_short("Guard house");
set_long("You are standing in the guardhouse at"
     +" the north end of this little town.  It is made entirely of"
     +" wood, and is sparsely furnished. To the north you can see"
	 + " the house of the village mayor, built wall-to-wall with"
         + " the guardhouse. Southeast you can see a crossroad.\n");

add_exit(RHUN_DIR+"stown6/crossroads","southeast",0);
add_exit(RHUN_DIR + "stown6/mayor_house","north",0);

add_prop(ROOM_I_LIGHT,1);
add_prop(ROOM_I_INSIDE,1);

    reset_room();
}

