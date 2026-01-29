/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("To the southeast rests some forest, tucked in a small " +
        "nook within the foothills. The road continues to the southwest " +
        "and northeast.\n");
    
    AI("forest","The forest invites exploration.\n");
    AI(({"nook","small nook"}),"The nook contains a small piece of " +
        "forest.\n");

    AE(TROOM + "road8", "southwest", 0, 2);
    AE(TROOM + "road10", "northeast", 0, 2);
    AE(TROOM + "forest8", "southeast", 0, 2, 1);
    reset_tant_room();
}

