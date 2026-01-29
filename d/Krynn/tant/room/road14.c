/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("The road continues to the northeast and south. It seems " +
        "that someone camped along the roadside in this location, as a " +
        "campfire has recently been put out. The city of Tantallon can " +
        "be seen in the distance.\n");
    AI(({"city","tantallon","city of tantallon"}),"The city of Tantallon " +
        "rests to the northeast, nestled in the Forsaken Mountains.\n");
    AI("campfire","The campfire is entirely out, although some sticks " +
        "still remain nearby.\n");
    AI("sticks","Some of the sticks might be usable torches.\n");
    AI("stick","There are a few sticks located near the old campfire.\n");
    
    add_search(({"sticks","campfire"}),4,TOBJ + "torch", -3);

    AE(TROOM + "road15", "northeast", 0, 2);
    AE(TROOM + "road13", "south", 0, 2);
    reset_tant_room(); 
}

