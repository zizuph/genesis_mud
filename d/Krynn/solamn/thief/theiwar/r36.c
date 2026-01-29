/* created by Aridor 04/19/94 */

#include "../local.h"

inherit MININGROOM;


void
create_mining_room()
{
    set_my_long("Here, the cavern branches. The hall to the northeast leads " +
        "upwards, whereas towards the southwest the cavern stays at " +
        "the same level. A hallway, with smooth walls and the typical " +
        "dwarven design continues north, completely mismatching " +
        "the torn walls, ceiling and floor here in the cavern, the result " +
        "of greedy dwarves ploughing through the hard rock here under " +
        "the mountain. ");

    add_exit(THEIWAR + "r34","southwest");
    add_exit(THEIWAR + "r37","north");
    add_exit(THEIWAR + "r27","northeast","@@upwards");

    what1 = "silver";

}


void
reset_mining_room()
{
    num1 = random(6);
}


int
upwards()
{
    write("The cavern slopes noticeably upwards as you walk to the northeast.\n");
    return 0;
}
