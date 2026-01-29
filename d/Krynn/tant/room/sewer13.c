/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The sewer pipe seems to end in a dead end. To the west " +
        "is a blockage, which causes it to be too small for you to pass. " +
        "It seems this part of the pipe gets blocked frequently, as it " +
        "looks like it is cleared every so often. The pipe leads " +
        "back east.\n");

    ACI(({"blockage","metal pipe","pipe"}),"clear","@@go_west");

    set_dircmd("blockage");    

    AE(TROOM + "sewer5", "east", 0, 1);
    reset_tant_room();
}

go_west()
{
    write("You clear some of the blockage and manage to slip through!\n");
    TP->move_living("through a cleared section of the blockage",
        TROOM + "sewer14", 0, 0);
    return "";
}

