/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a pier in a cavern. There is an underground bay " +
	     "opening up to the north from here. A cavern leads further " +
	     "into the mountain to the south and the pier extends " +
	     "east. You can see a faint light coming from somewhere " +
	     "around a corner in the north.\n");
    
    add_exit(CAVERN + "har4","south");
    add_exit(CAVERN + "har6","east");
    
    DARK;
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
}
