
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"You are making your way along the road in Rhun, which here"
	+" heads out across the plains."
	+"  The forest of northeastern Rhun is in sight to the"
	+" west"
	+", while the plains of Rhun and beyond stretch endlessly out to"
	+" the east"
	+"."
     +"\n",75));

AE(RHUN+"roads/section8/p","north",0);
AE(RHUN+"roads/section8/r","south",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("A forest of tall, dark trees topped with"
	+" thick green leaves stands off to the"
	+" west"
	+".\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
