
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains, north of the town");
set_long(break_string(
	"You stand on a wide and very-old dirt road in Rhun in"
	+" eastern Rhovanion.  It leads off to the"
	+" northeast"
	+" from here,"
	+" and enters a small town just to the"
	+" southwest"
	+".  Off to the north stands a great forest of dark trees."
     +"\n",75));

AE(RHUN+"roads/section8/af","northeast",0);
AE(RHUN+"stown6/road_ne","southwest",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("A forest of tall, dark trees"
	+" topped with thick green leaves lies off to the"
	+" north"
	+" from here.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));
add_item("town",break_string("The small town lies just to the"
	+" southwest."
    +"  Why don't you stop in and visit?\n", 75));

add_prop(ROOM_I_LIGHT,1);

}
