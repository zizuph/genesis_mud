
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains");
set_long(break_string(
	"This is a wide and very old dirt road, which leads across"
	+" the plains of Rhun in eastern Rhovanion."
	+"  To the"
	+" north"
	+", you can see a large, shadowy forest of dense trees."
     +"\n",75));

AE(RHUN+"roads/section8/ad","northeast",0);
AE(RHUN+"roads/section8/af","southwest",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item("forest",break_string("A dense forest of tall, dark trees"
	+" topped with thick green leaves stands off to the"
	+" north"	
	+".\n",75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));

add_prop(ROOM_I_LIGHT,1);

}
