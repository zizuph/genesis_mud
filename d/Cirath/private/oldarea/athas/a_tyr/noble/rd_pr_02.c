/* rd_pr_02: Promenade section 2: Serpine, 12-03-96 */
 
inherit "/std/room";
#include "defs.h"
 
void
create_room()
{
    set_short("crossroad of High Road and the Promenade");
 set_long("Once in a moment of excess the nobles of Tyr decided that "
            +"they shouldn't ever have to withstand the sun's rays "
            +"and began to roof the entire district.  A short span "
            +"into the project it was abandoned, but the foundation "
            +"still stands here today: The entire square is capped "
            +"by a structure of stone, chitin, and hide. Rather then "
            +"blocking the heat, the roof seems instead to hold it in, "
      +"so few of the wealthier class linger long at this "
            +"place.  You don't wish to either, and with roads "
            +"in four directions, there is little need to.\n");
            
    add_item(({"structure", "roof"}), "Kalak has refused to allow the "
      +"nobles to tear it down. Too much precious irony.\n");
 
    OUTSIDE
    ADD_SUN_ITEM;
 
    add_exit(TZ_NOBLE+"rd_pr_01.c", "north", "@@roof_message", 5);
    add_exit(TZ_NOBLE+"rd_hr_04.c", "east", "@@roof_message", 5);
    add_exit(TZ_NOBLE+"rd_pr_03.c", "south", "@@roof_message", 1);
    add_exit(TZ_NOBLE+"rd_hr_03.c", "west", "@@roof_message", 1);
}
 
public int
roof_message()
{
    TP->catch_msg("The temperature drops somewhat as you leave the "
                 +"confines of the Great Roof.\n");
    return 0;
}
