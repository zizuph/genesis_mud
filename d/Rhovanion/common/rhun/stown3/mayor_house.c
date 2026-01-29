#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
#pragma save_binary

inherit RHUN + "stowns/mayor_master";

create_room()
{
set_short("Mayor's house");
set_long(break_string("This is the home of the mayor of this"
     +" town.  It is a bit more well-furnished than others"
     +" in town, though still not especially impressive.  The exit"
     +" heads back to the southeast.\n",75));

AE(RHUN+"stown3/crossroads","southeast",0);

add_prop(ROOM_I_LIGHT,1);IN

    reset_room();
}
