
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
	+"  You may leave the road here and head off into the trees"
	+" to the"
	+" north"
	+" if you choose."
     +"\n",75));

AE(RHUN+"roads/section8/k","east",0);
AE(RHUN+"roads/section8/i","west",0);
AE(RHUN+"forest/m5","north",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("The forest stands on both sides of"
	+" the road, its overhanging branches shadowing your way"
	+".\n",75));

add_prop(ROOM_I_LIGHT,1);

}
