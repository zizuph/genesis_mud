/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer here is bent in an L-shape, heading east and " +
        "south.\n");

    AE(TROOM + "sewer22", "east", 0, 1);
    AE(TROOM + "sewer26", "south", 0, 1);
    reset_tant_room();
}

