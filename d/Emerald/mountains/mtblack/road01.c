/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

void
create_road()
{
    set_long("   The dull, gray rocky road extends out to the northwest "+
	     "before you. The road follows a winding course at the base "+
	     "of the enormous, towering mountains which gradually heads "+
	     "northwest. The black mountain's narrow, jagged peak stands "+
        "solidly in the sky against the ever-shifting clouds. Just "+
	     "barely visible here is a second, shorter mountain behind "+
	     "the black mountain. It has a flat peak which is continually "+
	     "spewing forth a dark, noxious-looking plume of smoke.\n\n");

    add_exit(MBLACK_DIR + "road02", "northwest");
    add_exit(LROAD_DIR + "road36", "southeast");
}
