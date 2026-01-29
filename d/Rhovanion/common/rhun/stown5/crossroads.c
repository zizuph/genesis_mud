
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Crossroads");
set_long(break_string("This is a small crossroads at the center of"
     +" this tiny town.  To the northwest and south lie two small"
     +" buildings. You may head down a small path to the east, or"
     +" head off into the forest to the north or west."
     +"\n",75));

AE(RHUN+"stown5/empty_nw","northwest",0);
AE(RHUN+"stown5/empty_s","south",0);
AE(RHUN+"stown5/eastside","east",0);
AE(RHUN+"forest/k12","north",0);
AE(RHUN+"forest/j13","west",0);

add_item(({"building","buildings"}),break_string("Two small, wooden"
	+" buildings lie nearby.  THey were apparently abandoned"
	+" long ago.\n",75));
add_item("path", break_string("The path leads east from here to another"
    +" part of this small, abandoned town.\n", 75));

add_prop(ROOM_I_LIGHT,1);

}
