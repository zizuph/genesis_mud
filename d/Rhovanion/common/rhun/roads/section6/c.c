
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road");
set_long(break_string("The dirt road forks here."
	+"  The main way continues on, heading toward a small town to the west"
	+" while approaching a large, dense forest of tall trees"
	+" off to the east."
	+"  Meanwhile, a southern branch heads toward a large town"
	+" near the mouth of the River Carnen as it empties into"
	+" the Sea of Rhun."
     +"\n",75));

AE(RHUN+"roads/section6/d","east",0);
AE(RHUN+"roads/section6/b","west",0);
AE(RHUN+"roads/section7/a","south",0);

add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),break_string("The Sea"
	+" of Rhun lies just to the"
	+" south"
	+".  It stretches on for leagues"
	+" in that direction"
	+", passing out of the range of sight.\n",75));
add_item("road",break_string("The road is made of dirt, but is well-marked."
	+"  It leads off from here to the"
	+" east, west and south"
	+"."
	+"\n",75));
add_item("plains",break_string("The plains lie off to the north, stretching"
	+" on seemingly forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
