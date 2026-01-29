
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"You travel on a dirt road over the plains."
	+"  To the"
	+" north"
	+" is the River Carnen, rushing down from the Iron Hills"
	+" in the far north."
     +"\n",75));

AE(RHUN+"roads/section1/c","north",0);
AE(RHUN+"roads/section1/a","southeast",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"river","River Carnen","river carnen"}),break_string("The"
	+" river lies off to the north."
	+"  You can hear it as it flows rapidly by.\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
