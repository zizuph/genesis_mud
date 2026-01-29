
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"You are making your way along the road in Rhun, which here"
	+" heads out across the plains."
	+"  The Sea of Rhun is in sight to the"
	+" south"
	+", while the forest of northeastern Rhun"
	+" can be seen"
	+" to the"
	+" east"
	+"."
     +"\n",75));

AE(RHUN+"roads/section6/f","east",0);
AE(RHUN+"roads/section6/d","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),
	break_string("The Sea of Rhun lies just to the south,"
	+" stretching on seemingly forever.\n",75));
add_item("forest",break_string("The dense forest of tall, dark"
	+" trees topped with thick green leaves lies off to the"
	+" east, covering the northeastern tip of the Sea"
	+" of Rhun.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
