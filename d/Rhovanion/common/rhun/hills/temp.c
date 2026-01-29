
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("The plains are not yet open.");
set_long(break_string("The way across"
	+" the plains toward the Sea of Rhun is not"
	+" yet open for exploration.  Your only option"
	+" here is to head back onto the road to the"
	+" west."
     +"\n",75));

AE(RHUN+"roads/section5/c","west",0);

}
