/* created by Aridor 04/19/94 */

#include "../local.h"

inherit MININGROOM;


void
create_mining_room()
{
    set_my_long("This cavern is leading into three directions. The walls " +
        "don't look normal here, " +
        "holes and cuts and traces of labor are visible everywhere. " +
        "A small trickle of water drips down from the ceiling, flowing " +
        "off to the southeast, wetting the floor here. ");

    add_exit(THEIWAR + "r36","northeast");
    add_exit(THEIWAR + "r33","west");
    add_exit(THEIWAR + "r35","southeast");

    what1 = "gold";
    what2 = "silver";
}


void
reset_mining_room()
{
    num1 = random(4);
    num2 = random(7);
}
