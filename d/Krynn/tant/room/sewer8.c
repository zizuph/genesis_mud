/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe continues northwest and northeast, " +
        "as well as south.\n");

    AE(TROOM + "sewer10", "northwest", 0, 1);
    AE(TROOM + "sewer9", "northeast", 0, 1);
    AE(TROOM + "sewer7", "south", 0, 1);
    reset_tant_room();
}

