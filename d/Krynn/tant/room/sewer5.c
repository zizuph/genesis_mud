/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe branches in three directions here: west, " +
        "southwest, and north.\n");

    AE(TROOM + "sewer4", "southwest", 0, 1);
    AE(TROOM + "sewer13", "west", 0, 1);
    AE(TROOM + "sewer6", "north", 0, 1);
    reset_tant_room();
}

