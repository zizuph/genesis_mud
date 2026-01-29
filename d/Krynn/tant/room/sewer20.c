/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("This is a dead end, with only the pipe leading northeast.\n");

    AE(TROOM + "sewer14", "northeast", 0, 1);
    reset_tant_room();
}

