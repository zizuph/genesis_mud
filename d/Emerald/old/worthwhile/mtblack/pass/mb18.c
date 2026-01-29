/* MB18.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit MBLACK_DIR + "pass/pass_common";

void
create_pass()
{
	set_short("A trail near the summit of Mt. Black");
   add_my_desc("\n\n");

	add_exit(MBLACK_DIR + "pass/mb19", "northwest",0,0);
	add_exit(MBLACK_DIR + "pass/mb17", "south",0,0);
}
