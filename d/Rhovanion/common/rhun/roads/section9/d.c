
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road, on the plains,  southwest of the town");
set_long(break_string(
	"You stand on a wide and very-old dirt road in Rhun in"
	+" eastern Rhovanion.  It leads off to the northeast from here, "
	+"and heads toward some dilapidated ruins just to the"
	+" southwest."
     +"\n",75));

AE(RHUN+"ruins/to_road","southwest",0);
AE(RHUN+"roads/section9/c","northeast",0);

add_item("road",break_string("The road is made of dirt, but it"
	+" is quite well-marked."
	+"\n",75));
add_item(({"Sea", "sea", "Sea of Rhun", "sea of rhun"}), 
	break_string("The Sea of Rhun lies off to the west from here."
	+"  You can hear the waves crash against its shores.\n", 75));
add_item("plains",break_string("The plains of Rhun seem to stretch on"
	+" forever.\n",75));
add_item("ruins",break_string("The ruins consist of fallen stone"
	+" structures of various shapes.  Perhaps the place was once"
	+" a shrine?"
	+"  It lies off to the southwest."
	+"\n", 75));  

add_prop(ROOM_I_LIGHT,1);

}
