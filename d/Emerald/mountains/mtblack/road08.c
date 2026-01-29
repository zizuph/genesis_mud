/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

void
create_road()
{
    set_long("   The dull, gray stone-covered road begins to widen "+
	     "and lose some of its stifling volcanic edge as it "+
	     "contiues further north toward the water's edge. The "+
	     "huge volcano towers over the road, its flat, gray "+
	     "peak continuously spewing forth a thick plume of "+
	     "black smoke. Looking south along the road, beyond the "+
	     "volcano there is a huge, towering black mountain. Its "+
	     "peak reaches almost twice the height of the volcano. The "+
	     "jagged, narrow peak seams to reach up and scrape the "+
	     "bottom of the clouds as they drift by.\n\n");

    add_item( ({"water", "water's edge", "water edge"}),
	     "The water's edge is barely visible from here, the volcano "+
	     "blocks most of it out. However, you can make out that "+
	     "the water is calm and there are piers out on the water. Now "+
	     "that you stop and take the time to look down there, you "+
	     "think you can distinguish the faint smell of salt water "+
	     "in the air.\n");

    add_item("piers",
	     "You can't quite make out the piers from here.\n");

    add_exit(MBLACK_DIR + "road09", "north");
    add_exit(MBLACK_DIR + "road07", "southeast");
}
