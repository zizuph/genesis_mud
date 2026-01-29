
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"The road fizzles out, disappearing here.  Apparently"
	+" whoever was working on it decided that continuing"
	+" wasn't worth the effort.  To the south, east and west,"
	+" nothing but the vast plains of Rhun stands.  You may follow the"
	+" road back to the northeast."
     +"\n",75));

AE(RHUN+"roads/section2/k","northeast",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));

add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
