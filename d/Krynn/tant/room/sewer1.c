/* Sewer in Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit SEWERBASE;


public void
create_sewer()
{
    add_my_desc("The wall of the pipe is scratched in this location. The " +
        "sewer pipe continues north, while the sewage flows out of the " +
        "pipe.\n");

    AI(({"scratches","scratch"}),"The scratches form these remnants of " +
        "words:\n    Sk..e.on. ro.m w...in!\n");

    AE(TROOM + "sewer2", "north", 0, 1);
    AE(TROOM + "road16", "out", 0, 1);
    reset_tant_room();
}

