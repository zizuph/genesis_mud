/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("This is a dead end. The pipe leads back east.\n");

    AE(TROOM + "sewer2", "east", 0, 1);
    reset_tant_room();
}

