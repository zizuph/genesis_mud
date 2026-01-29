/* MB2.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit MBLACK_DIR + "pass/path_common";

void
create_path()
{
	set_short("On a path on Mt. Black");
	add_my_desc("The path here is steep but passible. For just a "+
		"moment the mist clears and you can see black cliffs, "+
		"rising to the northeast.\n\n"); 
	
	add_item(({"cliffs", "black cliffs"}), "The mist clears a bit and "+
		"you can see the cliffs rising tall and sheer and black "+
		"as night.\n");
	add_exit(MBLACK_DIR + "pass/mb3", "northeast",0,0);
	add_exit(MBLACK_DIR + "pass/mb1", "southwest",0,0);	
}



