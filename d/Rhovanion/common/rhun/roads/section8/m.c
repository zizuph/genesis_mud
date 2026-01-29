
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
	+"The forest of northeastern Rhun stands just to the west."
	+"  The road enters as it heads in that direction"
	+".  Meanwhile, the plains of far northeastern Rhovanion and beyond"
	+" lie to the north and east, seemingly neverending"
	+"."
     +"\n",75));

AE(RHUN+"roads/section8/n","east",0);
AE(RHUN+"roads/section8/l","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"  It enters the forest to the west."
	+"\n",75));
add_item("forest",break_string("A forest of tall, dark trees"
	+" stands off to the"
	+" west"
	+" from here.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
