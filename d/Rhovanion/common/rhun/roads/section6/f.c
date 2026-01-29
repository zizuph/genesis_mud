
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
	+" south"
	+", you can see the vast Sea of Rhun, while to the"
	+" east, there is a large, shadowy forest of dense trees."
     +"\n",75));

AE(RHUN+"roads/section6/g","east",0);
AE(RHUN+"roads/section6/e","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),
	break_string("The Sea of Rhun lies off to the south,"
	+" stretching endlessly onward.\n",75));
add_item("forest",break_string("The forest lies just to the east,"
	+" full of densely-packed, tall trees.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
