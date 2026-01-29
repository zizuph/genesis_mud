#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
inherit RHUN + "stowns/guard_master";

create_room()
{
set_short("Guard house");
set_long(break_string("You are standing in the guardhouse at"
     +" the north end of this little town.  It is made entirely of"
     +" wood, and is sparsely furnished.  The only exit from it"
     +" leads southeast to a crossroads.\n",75));

AE(RHUN+"stown2/crossroads","southeast",0);

add_prop(ROOM_I_LIGHT,1);IN

    reset_room();
}
