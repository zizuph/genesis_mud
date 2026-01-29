/* rd_pr_01: Promenade section 1: Serpine, 12-04-96 */
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"
 
void
create_room()
{
    set_short("north end of the Promenade");
    set_long("This near to the edge of the city wall, the Quarter "
            +"becomes more sparsely inhabited and a bit less opulent. "
            +"A few small shops are even scattered to the north and "
            +"northeast.\n");
 
    add_item(({"shops", "shop"}), "Sand leads from a door to the north "
            +"and an odd smell drifts from the northeast.\n");
 
    add_item(({"city wall", "wall"}), "The towering wall keeps Tyr's "
            +"nobles safe from outside attack.\n");
 
    OUTSIDE
    ADD_SUN_ITEM;
 
    add_exit(TZ_NOBLE+"shinsand.c", "north", "@@block_exit@@", 1);
    add_exit(TZ_NOBLE+"colrscnt.c", "northeast", "@@block_exit@@", 1);
    add_exit(TZ_NOBLE+"rd_pr_02.c", "south", "@@roof_message", 1);
}
 
public int
roof_message()
{
    TP->catch_msg("The temperature increases as you "
                 +"enter the shade of the Great Roof.\n");
    return 0;
}
