
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Edge of town");
set_long(break_string("This rough dirt road leads out of town here,"
     +" heading off to the northeast.  You may also follow it southwest"
     +" toward the center of town."
     +"\n",75));

AE(RHUN+"stown6/crossroads","southwest",0);
AE(RHUN+"roads/section8/ag","northeast",0);

add_prop(ROOM_I_LIGHT,1);

}

