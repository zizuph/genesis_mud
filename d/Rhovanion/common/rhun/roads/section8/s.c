
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
	+" north to southeast"
	+".  "
	+"A large, dense forest lies to the"
	+" west"
	+", while the plains continue to stretch endlessly out to the"
	+" east, for as far as you can see, and then beyond"
	+"."
     +"\n",75));

AE(RHUN+"roads/section8/t","southeast",0);
AE(RHUN+"roads/section8/r","north",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("A forest of tall, dark trees"
	+" stands off to the"
	+" west"
	+" from here.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
