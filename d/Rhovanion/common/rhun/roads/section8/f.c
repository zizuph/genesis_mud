
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"This forest seems oddly silent around you"
	+"  Still, you press on, taking the dirt road"
	+" from east to west."
     +"\n",75));

AE(RHUN+"roads/section8/g","east",0);
AE(RHUN+"roads/section8/e","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("The forest stands on both sides of"
	+" the road, its overhanging branches shadowing your way"
	+".\n",75));

add_prop(ROOM_I_LIGHT,1);

}
