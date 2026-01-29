/* MB1.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"


void
create_path()
{
	set_short("At the base of Mt. Black");
	set_long("   You are at the start of a narrow pass over the "+
		"mountains near the base of Mt. Black. The jagged peak "+
		"stands out against a backdrop of dense,shifting clouds. +
		"The path rises gently toward the northeast then "+
		"dissapears into a thick mist.\n\n)";
	
	add_exit(MBLACK_DIR + "pass/mb2", "northeast",0,0);
	add_exit(MBLACK_DIR + "road05", "southwest",0,0);	
}



