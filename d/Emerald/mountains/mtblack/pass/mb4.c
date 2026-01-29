/* MB4.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit MBLACK_DIR + "pass/path_common";

void
create_path()
{
	set_short("A steep path on Mt. Black");
	add_my_desc("The path is quite steep here and you are beginning "+
		"to grow tired from the exertion of climbing.  The mist "+
		"clings to your body tenaciously and mingles with the sweat "+
		"of your exertion, chilling you further. The way this mist "+
           "moves you begin to feel that it has a mind of "+
		"it's own.\n\n");
	
	add_exit(MBLACK_DIR + "pass/mb5", "north",0,0);
	add_exit(MBLACK_DIR + "pass/mb3", "south",0,0);	
}



