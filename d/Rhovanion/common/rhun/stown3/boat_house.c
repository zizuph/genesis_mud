
#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Boat House");
set_long(break_string("This is a large wooden building where the local"
	+" shipwright apparently does his planning and construction."
	+"  Shards of various types of wood are scattered across the"
	+" floor, along with mounds of sawdust.  The proprietor, however,"
	+" is apparently not here right now.  The only exit is back onto"
	+" the street to the west."
	+"\n",75));

AE(RHUN+"stown3/south_road","west",0);

add_prop(ROOM_I_LIGHT,1);IN

  add_item("sawdust", "The sawdust covers the floor in a thick layer. "+
                      "It makes you want to sneeze...\nACHOO!!\n");
add_item(({"shards","shard","wood"}),break_string("The wood comprises"
	+" the shipwright's half-finished projects.  It is of no real"
	+" interest, though.\n",75));

}
