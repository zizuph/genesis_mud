/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a pier in a cavern. There is an underground bay " +
	     "opening up to the north from here. The pier leads " +
	     "southwest from here along the waterline. " +
	     "You can see a faint light coming from somewhere " +
	     "around a corner in the north.\n");
    
    add_exit(CAVERN + "har6","southwest");
    
    DARK;
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
}
