/* MB1.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"
inherit "/std/room";

void
create_room()
{
	set_short("At the base of Mount Black");
	set_long("   You are at the start of a narrow pass over the "+
		"mountains near the base of Mount Black. It's black "+
		"stone glistens with recent rainfall as it climbs up "+
		"out of the earth and soars into the sky, its jagged "+
		"peak standing against the backdrop of shifting clouds. "+
		"The path rises gently toward the northeast then "+
		"disappears into a thick mist.\n\n");
	
	add_item(({"trail", "path", "pass"}), "The path leads to the "+
		"northeast and up the mountian.  You cannot see all of "+
		"it but rather scattered pieces as the mist clears here "+
		"and there.\n");
	add_item(({"Mt. Black", "mountain", "mount black"}), "The jagged "+
		"black mountain rises high above you seeming to touch "+
		"the very heavens.\n");
	add_item(({"mist", "fog"}), "The mist seems to be alive as it "+
		"twists and swirls around, alternately concealing and "+
		"revealing the path ahead as well as the other features "+
		"of the landscape.\n");
	add_item(({"sky"}), "You can't see much of the sky above you "+
		"because the mountian is so close it fills your sight.\n");

	add_exit(MBLACK_DIR + "pass/mb2", "northeast",0,0);
	add_exit(MBLACK_DIR + "road05", "southwest",0,0);	
}
