/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe leads north and southwest.\n");

    AE(TROOM + "sewer6", "southwest", 0, 1);
    AE(TROOM + "sewer8", "north", 0, 1);
    reset_tant_room();
}

