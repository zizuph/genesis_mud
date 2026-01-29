/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("This is a dead end. The sewer pipe continues southwest.\n");

    AE(TROOM + "sewer8", "southwest", 0, 1);
    reset_tant_room();
}

