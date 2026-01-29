/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe branches northeast and south.\n");

    AE(TROOM + "sewer5", "northeast", 0, 1);
    AE(TROOM + "sewer3", "south", 0, 1);
    reset_tant_room();
}

