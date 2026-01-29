/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe branches northwest and northeast, " +
        "as well as south.\n");

    AE(TROOM + "sewer11", "northwest", 0, 1);
    AE(TROOM + "sewer7", "northeast", 0, 1);
    AE(TROOM + "sewer5", "south", 0, 1);
    reset_tant_room();
}

