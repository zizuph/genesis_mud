
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road");
set_long(break_string("You are travelling on a dirt road"
     +" in Rhun.  Off to the south and east, you can see the vast expanse"
     +" of the Sea of Rhun, while to the north lies the River Carnen, rushing"
     +" south and east to empty into the sea, and beyond it, the vast and"
     +" empty plains of Rhun."
     +"  The road curves here from east to southwest."
     +"\n",75));

AE(RHUN+"roads/section5/c","east",0);
AE(RHUN+"roads/section5/a","southwest",0);

add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),break_string("The Sea"
	+" of Rhun lies just to the southeast.  It stretches on for leagues"
	+" to the east and south, passing out of the range of sight.\n",75));
add_item(({"river","river carnen","River Carnen"}),break_string("The"
	+" River Carnen flows south and east into the Sea of Rhun, having its"
	+" origins in the Iron Hills far to the north.\n",75));
add_item("road",break_string("The road is made of dirt, but is well-marked."
	+"  It heads from east to southwest here."
	+"\n",75));
add_item("plains",break_string("The plains lie to the north, stretching"
	+" on seemingly forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
