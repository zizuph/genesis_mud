/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("This is a T-intersection of the pipes, leading both " +
        "north and south, as well as east.\n");

    AE(TROOM + "sewer27", "north", 0, 1);
    AE(TROOM + "sewer23", "east", 0, 1);
    AE(TROOM + "sewer25", "south", 0, 1);
    reset_tant_room();
}

