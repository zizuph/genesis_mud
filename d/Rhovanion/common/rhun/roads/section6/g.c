
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"You travel on a dirt road over the plains."
	+"  To the east is a large, green forest."
     +"\n",75));

AE(RHUN+"roads/section6/h","east",0);
AE(RHUN+"roads/section6/f","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("The forest is comprised"
	+" of many tall, densely-packed trees topped with a thick"
	+" canopy of dark green leaves.  It lies just off to the"
	+" east.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
