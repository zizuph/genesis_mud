/* created by Aridor 04/19/94 */

#include "../local.h"

inherit MININGROOM;


void
create_mining_room()
{
    set_my_long("A cavern that leads east. The walls don't look normal here, " +
        "holes and cuts and traces of labor are visible everywhere. " +
        "A narrow hole leads upwards from here, some sort of crude " +
        "stairs cut into the stone provide a relatively easy means " +
        "to get there. ");

    add_exit(THEIWAR + "r25","east");
    add_exit(THEIWAR + "r33","up");

    what1 = "gold";
    what2 = "iron";
    set_alarm(10.0,0.0,"reset_room");
}


void
reset_mining_room()
{
    num1 = random(4);
    num2 = random(9);
}
