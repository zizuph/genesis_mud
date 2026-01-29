/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("North and southwest are the two directions the pipes " +
        "lead.\n");

    AE(TROOM + "sewer2", "southwest", 0, 1);
    AE(TROOM + "sewer4", "north", 0, 1);
    reset_tant_room();
}

