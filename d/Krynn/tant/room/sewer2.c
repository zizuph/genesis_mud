/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The pipe branches in three directions: west, northeast, " +
        "and south.\n");

    AE(TROOM + "sewer21", "west", 0, 1);
    AE(TROOM + "sewer3", "northeast", 0, 1);
    AE(TROOM + "sewer1", "south", 0, 1);
    reset_tant_room();
}

