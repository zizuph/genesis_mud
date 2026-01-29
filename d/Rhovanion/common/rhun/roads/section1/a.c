
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("On the road");
set_long(break_string("You stand on a very-old and well-defined dirt road"
	+" in Rhun.  To the north lies the River Carnen, rushing"
	+" south and east to empty into the sea"
	+".  Beyond it to the north, and also off to the south"
	+" and west"
	+", stand the vast and"
	+" empty plains of Rhun."
	+"  A small town sits just to the"
	+" east,"
	+" and the road continues on to the"
	+" northwest."
     +"\n",75));

AE(RHUN+"roads/section1/b","northwest",0);
AE(RHUN+"stown1/roadnw","east",0);

add_item(({"river","river carnen","River Carnen"}),break_string("The"
	+" River Carnen flows south and east into the Sea of Rhun, having its"
	+" origins in the Iron Hills far to the north.\n",75));
add_item("road",break_string("The road is made of dirt, but is well-marked."
	+"  It heads from"
	+" east to northwest"
	+" here."
	+"\n",75));
add_item("plains",break_string("The plains lie to the"
	+" north, south and west"
	+", stretching"
	+" on seemingly forever.\n",75));
add_item("town",break_string("The little town lies just to the "
	+" east."
	+"  Why don't you stop in for a visit?\n",75));

add_prop(ROOM_I_LIGHT,1);

}
