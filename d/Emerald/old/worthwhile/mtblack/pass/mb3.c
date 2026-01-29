/* MB3.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit MBLACK_DIR + "pass/path_common";

void
create_path()
{
	set_short("On the path on Mt. Black");
	add_my_desc("The path is quite steep here.  That combined with "+
		"the mist-soaked ground has made the footing treacherous. "+
		"You begin to wonder why you decided to climb this "+
		"mountain. There seems to be nothing up this path except "+
		"the sheer black cliffs to the northeast.\n\n");
	
	add_item(({"cliffs", "black cliffs"}), "The coal black cliffs loom "+
		"ahead of you like dark sentinels hiding some deadly secret.\n");
	
	add_exit(MBLACK_DIR + "pass/mb4", "north",0,0);
	add_exit(MBLACK_DIR + "pass/mb2", "southwest",0,0);	
}



