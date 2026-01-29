/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("The road bends and twists, finally continuing northwest " +
        "and southwest.\n");

    AE(TROOM + "road9", "southwest", 0, 2);
    AE(TROOM + "road11", "northwest", 0, 2);
    reset_tant_room(); 
}

