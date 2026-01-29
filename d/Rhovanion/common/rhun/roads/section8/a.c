
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"You find yourself standing on a wide, well-defined"
	+" dirt road east of a small town.  On either side of"
	+" the road stand tall, dark trees casting heavy shadows"
	+" all around.  You may follow"
	+" this road off to the east, head south into the forest proper,"
	+" or enter the town to the west."
     +"\n",75));

AE(RHUN+"roads/section8/b","east",0);
AE(RHUN+"forest/d6","south",0);
AE(RHUN+"stown4/crossroads","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("The forest stands on both sides of"
	+" the road, its overhanging branches shadowing your way"
	+".\n",75));
add_item("town",break_string("The town is quite tiny, but"
	+" apparently still inhabited.  It lies just to"
	+" the west.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
