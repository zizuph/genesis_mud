
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, just inside the forest, west of town");
set_long(break_string(
	"The well-defined old dirt road heading into a small forest town here"
	+" to the east.  You may follow it out of the forest to the west."
     +"\n",75));

AE(RHUN+"stown4/road_w","east",0);
AE(RHUN+"roads/section6/h","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("The forest is made up of"
	+" many tall, densely-packed trees topped with thick green leaves."
	+"  You stand just inside it.  You may leave it by heading west."
	+"\n",75));
add_item("town",break_string("The small forest"
	+" town lies just to the east.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
