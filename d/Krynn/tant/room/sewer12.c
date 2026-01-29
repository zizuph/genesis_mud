/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("This is a dead end. The pipe leads south from here.\n");

    AE(TROOM + "sewer11", "south", 0, 1);
    reset_tant_room();
}

