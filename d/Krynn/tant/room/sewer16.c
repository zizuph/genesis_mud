/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe bends to the northwest and southwest.\n");

    AE(TROOM + "sewer15", "southwest", 0, 1);
    AE(TROOM + "sewer17", "northwest", 0, 1);
    reset_tant_room();
}

