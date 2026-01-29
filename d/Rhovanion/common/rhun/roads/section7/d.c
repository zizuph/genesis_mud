
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, outside a large town");
set_long(break_string(
	"The dirt road curves here, leading into town to the"
	+" south, or back out to the north."
	+"  Farther to the south, "
	+" you can see the vast Sea of Rhun."
     +"\n",75));

AE(RHUN+"roads/section7/c","northwest",0);
AE(RHUN+"ltown_ne/streets/northgate","south",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),
	break_string("The Sea of Rhun lies off to the south,"
	+" stretching endlessly onward.\n",75));
add_item("town",break_string("The town appears quite large"
	+" and, if not prosperous, at least self-supportive."
	+"  It lies just to the"
	+" south"
	+".\n",75));

add_prop(ROOM_I_LIGHT,1);

}
