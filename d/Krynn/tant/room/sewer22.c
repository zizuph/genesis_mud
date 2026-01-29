/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe bends to the west and southeast.\n");

    AE(TROOM + "sewer27", "west", 0, 1);
    AE(TROOM + "sewer19", "southeast", 0, 1);
    reset_tant_room();
}

