/* created by Aridor 04/19/94 */

#include "../local.h"

inherit MININGROOM;

#include RND_MEET

object dwarf;

void
create_mining_room()
{
    set_my_long("This could almost be called a hallway. A few bumps and " +
        "uneven rocks can still be seen. @@dwarf_desc@@ In one " +
        "corner, the easternmost of this hallway, nothing has " +
        "been worked on yet. ");

    add_exit(THEIWAR + "r31","north");
    add_exit(THEIWAR + "r23","southwest");

    what1 = "silver";
    set_alarm(1.0,0.0,"reset_room");
}


void
reset_mining_room()
{
    num1 = random(3);

    if (dwarf)
      return;
    dwarf = RANDOM_MEET(THEIWARTABLE);
    dwarf->move_living("xxx",TO);
}

string
dwarf_desc()
{
    if (dwarf)
      return "But the dwarf working here is smoothing out the " +
    "walls and expertly hammers and chisels here and there.";
    else
      return "";
}
