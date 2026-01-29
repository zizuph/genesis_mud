
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"You travel through a dense forest,"
	+" taking a well-defined, old dirt road from east to west."
	+"  The canopy of leaves and branches casts dark shadows on the"
	+" path as you pass."
	+"  You can leave the path and head into the forest from here"
	+" to the north."
     +"\n",75));

AE(RHUN+"roads/section8/h","east",0);
AE(RHUN+"roads/section8/f","west",0);
AE(RHUN+"forest/j5","north",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("The forest stands on both sides of"
	+" the road, its overhanging branches shadowing your way"
	+".\n",75));

add_prop(ROOM_I_LIGHT,1);

}
