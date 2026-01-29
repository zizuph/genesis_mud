/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("To the southwest is an inhabited area, although it is " +
        "difficult to tell who lives there, from your vantage point. The " +
        "road continues to the northeast.\n");

    AI(({"inhabited area","area"}),"You would have to go explore it, if you " +
        "want to satisfy your curiousity.\n");

    AE(S_FOREST, "southwest", 0, 2);
    AE(TROOM + "road2", "northeast", 0, 2);
    reset_tant_room(); 
}

