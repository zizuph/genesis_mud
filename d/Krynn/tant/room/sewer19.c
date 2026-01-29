/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("This is a junction of many sewer pipes. Branches leave " +
        "in all west directions, as well as northeast.\n");

    AE(TROOM + "sewer24", "southwest", 0, 1);
    AE(TROOM + "sewer23", "west", 0, 1);
    AE(TROOM + "sewer22", "northwest", 0, 1);
    AE(TROOM + "sewer18", "northeast", 0, 1);
    reset_tant_room();
}

