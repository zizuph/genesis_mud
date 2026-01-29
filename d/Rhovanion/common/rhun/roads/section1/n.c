
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
	+" west to southeast"
	+".  "
	+"The River Carnen lies off to the"
	+" north and east"
	+", making its way southeast to empty into the Sea of Rhun."
     +"\n",75));

AE(RHUN+"roads/section1/o","west");
AE(RHUN+"roads/section1/m","southeast");

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));

add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
