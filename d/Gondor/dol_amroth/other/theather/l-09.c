/*
 * other/theather/l-09
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

void
create_inside()
{
    set_short("inside a theater");
    set_long("This is inside a theater.\n");

    add_exit(DOL_OTHER + "streets/m-08", "northeast", 0, 1);
    add_exit(DOL_OTHER + "theather/l-10", "south", 0, 1);
}
