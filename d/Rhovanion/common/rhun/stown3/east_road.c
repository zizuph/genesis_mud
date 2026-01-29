
#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Road out of town");
set_long(break_string("The road heads out of this small town here,"
	+" leading off to the east.  You can also follow it back toward"
	+" the main parts of the town, just to the west."
	+"\n",75));

AE(RHUN+"stown3/crossroads", "west", 0);
AE(RHUN+"roads/section6/a", "east", 0);


add_prop(ROOM_I_LIGHT,1);

}
