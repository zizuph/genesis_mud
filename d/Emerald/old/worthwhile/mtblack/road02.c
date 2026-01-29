/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

void
create_road()
{
    set_long("   Standing on a long, dark, stone-covered road, you "+
	     "scan up along the east, tracing the length of a towering "+
	     "black mountain with a jagged, narrow peak. Being at the base "+
	     "of the mountains here, you almost have to double over "+
	     "backwards to see the peak. However, barely visible behind "+
	     "the black mountain is a shorter, wider mountain. The peak "+
	     "of this mountain is flat and continually spewing forth a "+
	     "dark plume of smoke. As the road moves away from the black "+
	     "mountain and toward the second mountain further to the "+
	     "northwest, you suspect you might get a better view.\n\n");

    add_exit(MBLACK_DIR + "road03", "northwest");
    add_exit(MBLACK_DIR + "road01", "southeast");
}
