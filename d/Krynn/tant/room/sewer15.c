/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer branches in three directions, northwest and " +
        "northeast, as well as southeast.\n");

    AE(TROOM + "sewer18", "northwest", 0, 1);
    AE(TROOM + "sewer16", "northeast", 0, 1);
    AE(TROOM + "sewer14", "southeast", 0, 1);
    reset_tant_room();
}

