
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road");
set_long(break_string("You stand on a very-old and well-defined dirt road"
	+" in Rhun.  The plains of Rhun stretch out around you."
	+"  A small town sits just to the"
	+" north,"
	+" and the road continues on to the"
	+" southeast."
     +"\n",75));

AE(RHUN+"roads/section4/b","southeast",0);
AE(RHUN+"stown2/road_s","north",0);


add_item("road",break_string("The road is made of dirt, but is well-marked."
	+"  It heads from"
	+" north to southeast"
	+" here."
	+"\n",75));
add_item("town",break_string("The little town lies just to the "
	+" north."
	+"  Why don't you stop in for a visit?\n",75));

add_prop(ROOM_I_LIGHT,1);

}
