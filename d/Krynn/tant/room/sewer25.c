/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe bends, leading north and east.\n");

    AE(TROOM + "sewer26", "north", 0, 1);
    AE(TROOM + "sewer24", "east", 0, 1);
    reset_tant_room();
}

