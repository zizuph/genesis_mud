/* Sewer under Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("There is a slight colour change in some of the sludge " +
        "in one area of the pipe. The pipe continues north and southeast.\n");

    AI("sludge","The sludge seems to contain something beneath.\n");

    add_search("sludge",5,TWEP + "rusty_dagger",-1);

    AE(TROOM + "sewer12", "north", 0, 1);
    AE(TROOM + "sewer6", "southeast", 0, 1);
    reset_tant_room();
}

