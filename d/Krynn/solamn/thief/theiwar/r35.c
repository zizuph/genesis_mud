/* created by Aridor 04/19/94 */

#include "../local.h"

inherit MININGROOM;

#include RND_MEET

object dwarf;

void
create_mining_room()
{
    set_my_long("You are standing at the end of a mine. Water gently flows " +
        "in from the northwest all over the floor and vanishes " +
        "into a tiny crack in the floor at the east wall.@@dwarf_des@@");

    add_exit(THEIWAR + "r34","northwest");

    what1 = "gold";
    what2 = "carbon";
    set_alarm(1.0,0.0,"reset_room");
}


void
reset_mining_room()
{
    num1 = random(6);
    num2 = random(3);

    if (dwarf)
      return;
    dwarf = RANDOM_MEET(THEIWARTABLE);
    dwarf->move_living("xxx",TO);
}

string
dwarf_des()
{
    if (dwarf && num1)
      return " A dwarf is busy working at one of the walls, trying to mine " +
    "a shimmering metal from it.";
    if (dwarf && !num1)
      return " A dwarf is sitting on a stone here and apparently takes a " +
    "break.";
    return "";
}

int
hook_mining_now(object who)
{
    if (!dwarf || E(dwarf) != TO)
      return 0;
    dwarf->command("emote rumbles: Leave THAT alone, will ya!!");
    dwarf->command("glare angrily");
    write("You jump back and decide not to continue mining.\n");
    dwarf->attack_object(who);
    return 1;
}
