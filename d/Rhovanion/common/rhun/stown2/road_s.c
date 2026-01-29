
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Edge of town");
set_long(break_string("This rough dirt road leads out of town here,"
     +" heading off to the south.  You may also follow it north"
     +" toward the center of town."
     +"\n",75));

AE(RHUN+"stown2/road_se","north",0);
AE(RHUN+"roads/section4/a","south",0);

add_prop(ROOM_I_LIGHT,1);

}

