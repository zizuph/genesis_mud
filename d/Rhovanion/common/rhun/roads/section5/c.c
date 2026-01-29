
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road");
set_long(break_string("The dirt road forks here.  Northward, it leads to"
     +" a small town.  An eastern branch heads out across the plains toward"
     +" the sea's edge, while the western one continues on inland."
     +"  Off to the south and east, you can see the vast expanse"
     +" of the Sea of Rhun, while to the north and west lies the River Carnen,"
     +" rushing"
     +" south and east to empty into the sea, and beyond it, the vast and"
     +" empty plains of Rhun."
     +"\n",75));

AE(RHUN+"roads/section5/d","north",0);
AE(RHUN+"roads/section5/b","west",0);
/* Commented out til Hills are open
AE(RHUN+"hills/plains","east",0);
*/
AE(RHUN+"hills/temp","east",0);

add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),break_string("The Sea"
	+" of Rhun lies just to the southeast.  It stretches on for leagues"
	+" to the east and south, passing out of the range of sight.\n",75));
add_item(({"river","river carnen","River Carnen"}),break_string("The"
	+" River Carnen flows south and east into the Sea of Rhun, having its"
	+" origins in the Iron Hills far to the north.\n",75));
add_item("road",break_string("The road is made of dirt, but is well-marked."
	+"  It leads off from here to the north, east and west."
	+"\n",75));
add_item("plains",break_string("The plains lie off to the north, stretching"
	+" on seemingly forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
