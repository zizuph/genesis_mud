
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
	+"  You can make your way between the trees and into the"
	+" forest proper by heading"
	+" north or south"
	+" from here."
     +"\n",75));

AE(RHUN+"roads/section8/i","east",0);
AE(RHUN+"roads/section8/g","west",0);
AE(RHUN+"forest/k5","north",0);
AE(RHUN+"forest/k6","south",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("The forest stands on both sides of"
	+" the road, its overhanging branches shadowing your way"
	+".\n",75));

add_prop(ROOM_I_LIGHT,1);

}
