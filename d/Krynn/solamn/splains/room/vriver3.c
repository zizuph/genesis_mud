inherit "/std/room";
#include <stdproperties.h>
#include "../local.h"

create_room()
{
    set_short("On the mighty Vingaard River");
    set_long("You are on the Vingaard River, which flows gently towards the " +
	     "northeast. To your southwest, the mighty Vingaard Keep rises " +
	     "towards the sky, its tall fortifications and walls making an " +
	     "impressive view. On the other side of the river, the east side, " +
	     "there is a forest visible further north and bushland directly " +
	     "to your east.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
