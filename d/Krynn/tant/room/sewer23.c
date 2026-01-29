/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe continues east and west.\n");

    AE(TROOM + "sewer26", "west", 0, 1);
    AE(TROOM + "sewer19", "east", 0, 1);
    reset_tant_room();
}

