/*mb23.c The path between Mt. Black and the volcano*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit MBLACK_DIR + "pass/vpath_common";

void
create_path()
{
	set_short("A dusty path");
	add_my_desc("\n\n");

	add_exit(MBLACK_DIR + "pass/mb22", "southeast",0,0);
	add_exit(MBLACK_DIR + "pass/mb24", "north",0,0);
}