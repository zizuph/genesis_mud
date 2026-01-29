/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe bends slightly, to the west and northeast.\n");

    AE(TROOM + "sewer25", "west", 0, 1);
    AE(TROOM + "sewer19", "northeast", 0, 1);
    reset_tant_room();
}

