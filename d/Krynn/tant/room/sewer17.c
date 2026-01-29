/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("This is a dead end, with the only exit being southeast.\n");

    AE(TROOM + "sewer16", "southeast", 0, 1);
    reset_tant_room();
}

