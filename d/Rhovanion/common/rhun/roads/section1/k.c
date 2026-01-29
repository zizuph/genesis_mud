
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"This is a wide and very old dirt road, which leads across"
	+" the plains of Rhun in northeastern Rhovanion."
	+"  To the"
	+" north and east"
	+", you can see the mighty River Carnen."
     +"\n",75));

AE(RHUN+"roads/section1/l","north",0);
AE(RHUN+"roads/section1/j","south",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"river","River","River Carnen","river carnen"}),
	break_string("The River Carnen lies off to the north and"
	+" east.  You can hear it as it flows swiftly southeast"
	+" toward the Sea of Rhun.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
