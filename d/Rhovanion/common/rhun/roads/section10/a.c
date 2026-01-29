
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains,  south of town");
set_long(break_string(
	"You stand on a wide and very-old dirt road in Rhun in"
	+" eastern Rhovanion.  It leads off to the south from here, "
	+"and enters a small town just to the north.  Off to the west"
	+" is the Sea of Rhun."
     +"\n",75));

AE(RHUN+"stown6/road_s","north",0);
AE(RHUN+"roads/section10/b","south",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"Sea", "sea", "Sea of Rhun", "sea of rhun"}), 
	break_string("The Sea of Rhun lies off to the west from here."
	+"  You can hear the waves crash against its shores.\n", 75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));
add_item("town", break_string("The small town lies just to the north."
    +"  Why don't you stop in and visit?\n", 75));

add_prop(ROOM_I_LIGHT,1);

}
