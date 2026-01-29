
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
	+"  Looking around, you see only vast, empty spaces in"
	+" all directions."
     +"\n",75));

AE(RHUN+"roads/section2/a","north",0);
AE(RHUN+"roads/section2/c","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));

add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
