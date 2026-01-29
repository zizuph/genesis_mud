/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe ends here, leaving only southeast as a " +
        "possible exit.\n");

    AE(TROOM + "sewer8", "southeast", 0, 1);
    reset_tant_room();
}

