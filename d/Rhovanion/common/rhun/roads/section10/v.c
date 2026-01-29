
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, outside the citadel");
set_long(break_string(
	"The dirt road runs across the plains of Rhun here from east to"
	+" west.  Off to the north is the Sea of Rhun, while southward"
	+" the flat, empty land stretches out of sight.  In the foothills"
	+" to the west stands a tall, dark citadel.  A cloud seems to hang"
	+" over the place, and you feel chilled just looking at it.  You"
	+" may approach the eastern wall of the place by following the"
	+" dirt road up into the foothills to the west, or leave back"
	+" to the east."
     +"\n",75));

AE(RHUN+"roads/section10/u","east",0);
AE(RHUN+"citadel/by_the_wall","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),
	break_string("The Sea of Rhun lies off to the north,"
	+" stretching on seemingly forever.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));
add_item("citadel",break_string("The citadel is a large fortress with"
	+" tall walls of dark stone.  It stands in the foothills just to the"
	+" west.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
