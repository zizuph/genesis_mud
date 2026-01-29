/* created by Aridor 02/21/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a cavern. It seems natural but to the southeast " +
	     "you can definitely see traces of hard labour. Huge blocks " +
	     "of stone are lying around and the cavern has been extended " +
	     "to the southeast, leaving a narrow opening which leads out " +
	     "of this cavern. The main part of the cavern leads further " +
	     "southwest.\n");
    
    add_exit(CAVERN + "pass4","southwest");
    add_exit(WATERFALL,"southeast");
    
    DARK;

    add_item("blocks","Someone must have been very strong to cut the rock " +
	     "into these blocks.\n");
}

