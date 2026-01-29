/* created by Aridor 02/21/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a natural cavern. A narrow opening leads upward " +
	     "and it looks possible to go there. The cavern itself " +
	     "continues northwards. The rock walls feel cold and damp " +
	     "to the touch.\n");
    
    add_exit(CAVERN + "pass1","up");
    add_exit(CAVERN + "pass3","north");
    
    DARK;
}

