inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"


create_room()
{
set_short("Low-hanging tunnel");
set_long("This is a low-hanging tunnel strewn with"
	+" cobwebs.  It opens into a large round chamber to the north, and"
	+" grows even smaller to the south.\n");

add_exit("/d/Avenir/common/dark/l4/center","north",0);
add_exit("/d/Avenir/common/dark/l4/s2","south",0);

add_item(({"cobweb","cobwebs"}), break_string("The cobwebs are"
	+" everywhere in this low tunnel, hanging in your face.\n",75));
AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");    

add_prop(ROOM_I_LIGHT,0);
IN

}
