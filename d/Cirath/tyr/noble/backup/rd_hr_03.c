/* rd_hr_03: High road section 3: Serpine, 04-07-95 */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("western high road");
    set_long("Nearer the center of the Noble's Quarter, the villas and "+
             "small mansions take on an odd and alien appearance. Their "+
             "bizarre and impracticle shapes seem to be an attempt by "+
             "nobles within to call attention to the vast sums they have "+
             "to waste, while the gardens and hanging vines are a slap "+
             "in the face to the water-starven civilization. One in "+
             "particular, a near sphere with reflective glass on top, "+
             "draws your attention north.\n");

    add_item(({"glass", "sphere"}), "Impossible to ignore, it reflects "+
             "the blinding rays of the sun in random directions. There "+
             "appear to be no guards.\n");

    add_item(({"villas", "villa", "mansions", "mansion"}), "True "+
             "monuments to conspicuous consumption; Most are heavily "+
             "guarded, walled, and just plain ugly.\n");

    add_item(({"garden", "gardens", "vine", "vines", "hanging vines"}), 
             "These collections of plants require a remarkable amount of "+
             "water, but at least are vaguely attractive.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_NOBLE+"house2.c", "north", 0, 1);
    add_exit(TYR_NOBLE+"rd_pr_02.c", "east", "@@roof_message", 1);
    add_exit(TYR_NOBLE+"rd_hr_02.c", "southwest", 0, 1);
}

public int
roof_message()
{
    TP->catch_msg("The temperature increases as you "
                 +"enter the shade of the Great Roof.\n");
    return 0;
}
