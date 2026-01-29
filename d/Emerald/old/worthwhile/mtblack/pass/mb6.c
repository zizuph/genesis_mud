/* MB6.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */


#include "/d/Emerald/defs.h"

inherit MBLACK_DIR + "pass/path_common";

void
create_path()
{
	set_short("A path on Mt. Black");
	add_my_desc("The path here is extremely steep as it climbs up through the "+
		"dense mist toward the black cliffs, and downward toward the "+
		"bottom of the Mountain.\n\n");
	
	add_item(({"cliffs", "black cliffs"}), "You can't see much "+
		"of the cliffs from here because they are almost completely "+
		"enshrouded in mist.\n");

	add_exit(MBLACK_DIR + "pass/mb7", "northeast",0,0);
	add_exit(MBLACK_DIR + "pass/mb5", "southwest",0,0);	
	
}



