/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe continues northwest and southwest, as " +
        "well as east.\n");

    AE(TROOM + "sewer20", "southwest", 0, 1);
    AE(TROOM + "sewer15", "northwest", 0, 1);
    AE(TROOM + "sewer13", "east", 0, 1);
    reset_tant_room();
}

