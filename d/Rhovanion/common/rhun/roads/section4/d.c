
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
	+" east and south"
	+", you can see the vast Sea of Rhun, along with"
	+" a rather large town."
     +"\n",75));

AE(RHUN+"roads/section4/e","south",0);
AE(RHUN+"roads/section4/c","northwest",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),
	break_string("The Sea of Rhun lies off to the"
	+" east and south,"
	+" stretching endlessly onward.\n",75));
add_item("town",break_string("The town appears quite large"
	+" and, if not prosperous, at least self-supportive."
	+"  It lies off to the"
	+" southeast"
	+".\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
