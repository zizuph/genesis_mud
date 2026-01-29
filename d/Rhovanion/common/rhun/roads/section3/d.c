
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"The road continues here across the plains of Rhun,"
	+" heading from "
	+" east to west"
	+".  "
	+"The River Carnen lies off to the"
	+" north"
	+", making its way southeast to empty into the Sea of Rhun."
     +"\n",75));

AE(RHUN+"roads/section3/e","east",0);
AE(RHUN+"roads/section3/c","west",0);

add_item(({"river","river carnen","River Carnen"}),break_string("The"
	+" River Carnen flows south and east into the Sea of Rhun, having its"
	+" origins in the Iron Hills far to the north.\n",75));
add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));

add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
