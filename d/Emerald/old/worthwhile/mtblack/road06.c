/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

void
create_road()
{
    set_long("   Standing at the base of a volcano, you look northwest "+
	     "down the dark, stone-covered road and south toward the "+
	     "giant, black mountain. Bits and pieces of volcanic rock "+
	     "and ash litter the road here and more to the northwest. "+
	     "The side of the volcano which soars up above the east side "+
	     "of the road is a dull, lifeless gray which is interrupted "+
	     "only on occasion by a few scattered clusters of dark "+
	     "green bushes and shrubbery.\n\n");

    add_exit(MBLACK_DIR + "road07", "northwest");
    add_exit(MBLACK_DIR + "road05", "south");
}
