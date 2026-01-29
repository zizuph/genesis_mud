
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"The road continues here through the trees, heading east to"
	+" west.  On its edges, the great trunks rise up, standing"
	+" densely packed."
     +"\n",75));

AE(RHUN+"roads/section8/c","east",0);
AE(RHUN+"roads/section8/a","west",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("The forest stands on both sides of"
	+" the road, its overhanging branches shadowing your way"
	+".\n",75));

add_prop(ROOM_I_LIGHT,1);

}
