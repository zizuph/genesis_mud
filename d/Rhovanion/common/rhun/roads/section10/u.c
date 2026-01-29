
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
	+" northeast to south"
	+".  "
	+"The Sea of Rhun lies off to the"
	+" north"
	+", a vast body of inland water fed from the north"
	+" by the mighty River Carnen."
	+"  Off to the west stands a large, dark, and rather foreboding"
	+" citadel."
     +"\n",75));

AE(RHUN+"roads/section10/t","north",0);
AE(RHUN+"roads/section10/v","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),
	break_string("The Sea of Rhun lies off to the north,"
	+" stretching on seemingly forever.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));
add_item("citadel",break_string("The citadel is a large fortress with"
	+" tall walls of dark stone.  It stands in the foothills off to the"
	+" west.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
