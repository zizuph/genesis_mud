/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("A cave can be seen in a nearby hillside. The road does " +
        "not wind here, but rather runs east and west.\n");
    AI("cave","The cave appears to be the lair of some filthy creatures.\n");
    AI("hillside","The cave is tucked away into the hillside.\n");

    ACI(({"cave","hillside cave","lair"}),"enter","@@go_cave");

    AE(TROOM + "road5", "west", 0, 2);
    AE(TROOM + "road7", "east", 0, 2);
    reset_tant_room();
}

go_cave()
{
    write("You summon up your courage and enter the cave.\n");
    set_dircmd("cave");
    TP->move_living("into the cave",TROOM + "goblin_lair", 0, 0);
    return "";
}
