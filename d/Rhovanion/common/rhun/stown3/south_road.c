
#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("South end of Main Street");
set_long(break_string("This is the southern end of this small town's"
	+" main street.  The road turns dusty as it heads southward"
	+" out of town.  To the east is a large wooden boat house,"
	+" apparently where the local shipwright does his design work."
	+"  Southwest from here stands a warehouse, and a wooden pier"
	+" extends into the swiftly-flowing River Carnen to the west."
	+"\n",75));

AE(RHUN+"stown3/bridge", "north", 0);
AE(RHUN+"stown3/boat_house", "east", 0);
AE(RHUN+"stown3/pier1","west",0);
AE(RHUN+"roads/section5/d","south",0);
AE(RHUN+"stown3/warehouse","southwest",0);

add_prop(ROOM_I_LIGHT,1);

}
