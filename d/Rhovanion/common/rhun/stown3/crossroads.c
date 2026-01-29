
#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Crossroads");
set_long(break_string("This is a crossroads at the north end of"
     +" this small town.  To the north lies a small wooden"
     +" building. You may head down the dirt road out of town to "
     +" the east, or down the town's main street off to the south."
     +" There is also a larger domicile-- perhaps the mayor's house?--"
     +" just to the northwest, and an abandoned old building of wood"
     +" to the southwest."
     +"\n",75));

AE(RHUN+"stown3/mayor_house","northwest",0);
AE(RHUN+"stown3/north_road","south",0);
AE(RHUN+"stown3/east_road","east",0);
AE(RHUN+"stown3/n_home","north",0);
AE(RHUN+"stown3/old_po","southwest",0);

add_item(({"building","buildings"}),break_string("Three wooden"
	+" buildings stand nearby, including a small house, an old,"
	+" abandoned post office, and the mayor's home.\n",75));
add_item(({"street","road"}), break_string("The road turns here to"
	+" lead away to the east and south.\n", 75));

add_prop(ROOM_I_LIGHT,1);

}