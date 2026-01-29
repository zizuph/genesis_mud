/* the inside of the tent
 *
 * Aridor 08/97
 */

#include "/d/Krynn/common/defs.h"

inherit R_FILE

void
create_krynn_room()
{
    set_short("Inside a decorated fancy tent");
    set_long("You are inside a decorated fancy tent. The owner of this tent " +
	     "appears to be very important.\n");
    INSIDE;
    NO_TIME;
}

int
quit(string str)
{
    write("You can't quit the realms from inside the tent. You will " +
        "need to exit first.\n");
    return 1;
}

void
init()
{
    ADA("quit");
    ::init();
}