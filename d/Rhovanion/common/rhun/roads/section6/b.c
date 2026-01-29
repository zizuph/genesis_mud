
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
+"The Sea of Rhun lies off to the"
	+" south"
	+", a vast body of inland water fed from the north"
	+" by the mighty River Carnen."
     +"\n",75));

AE(RHUN+"roads/section6/c","east",0);
AE(RHUN+"roads/section6/a","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));

add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
