/* created by Aridor 03/09/94 */

#include "../local.h"

inherit MININGROOM;

/* DIR1 leads out of the mountain, DIR2 into it */
#define DIR1  "north"
#define DIR2  "southwest"


void
create_mining_room()
{
    set_my_long("This is a normal hallway leading "+DIR1+" and "+DIR2+". However " +
        "the evenness of the walls is disturbed. Traces of mining, holes " +
        "and cuts, are visible on the walls here. A winding track leads " +
        "upwards into another cavern above, while pieces of rock lie " +
        "everywhere and you have to be careful not to trip over them. ");

    add_exit(THEIWAR + "r4",DIR1);
    add_exit(THEIWAR + "r6",DIR2);
    add_exit(THEIWAR + "r23","up");

    what1 = "silver";

    add_item(({"rocks","rock","pieces","debris"}),
         "This is just debris left lying around, without any value.\n");
    add_item(({"cuts","holes","wall","walls"}),
         "There are many holes and cuts in the walls here, the results " +
         "of the mining activity here.\n");
}


void
reset_mining_room()
{
    num1 = random(5);

}
