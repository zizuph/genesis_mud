/* MB5.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit MBLACK_DIR + "pass/path_common";

void
create_path()
{
	set_short("A path on Mt. Black");
	add_my_desc("The path here is so steep as to be almost "+
		"unclimbable. With every step your feet slip and "+
		"slide on the wet, moss covered ground.  Rising out of "+
		"the mist to the northeast are the black cliffs, sheer "+
		"and forboding.\n\n");
	
	add_item(({"cliffs", "black cliffs"}), "If you didn't know better "+
		"you might think these cliff were fashioned from night "+
		"itself.  So dark and pure is the blackness that it almost "+
		"hurts your eyes to look at them.\n");

	add_exit(MBLACK_DIR + "pass/mb6", "northeast",0,0);
	add_exit(MBLACK_DIR + "pass/mb4", "south",0,0);	
}



