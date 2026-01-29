/* created by Aridor 03/09/94 */

#include "../local.h"

inherit MININGROOM;

#include RND_MEET

object dwarf;

void
create_mining_room()
{
  set_my_long("The continuation of the iron ore mine apparently did not prove " +
          "too successful, in this direction. ");
  add_exit(THEIWAR + "r6", "northwest");
  add_exit(THEIWAR + "r7", "southeast", "@@closed");
  what1 = "iron";
  what2 = "silver";

}

void
reset_mining_room()
{
    num1 = random(9);
    num2 = random(4);

    if (dwarf)
      return;
    dwarf = RANDOM_MEET(THEIWARTABLE);
    dwarf->move_living("xxx",TO);
}


int
closed()
{
    write("This vein has hardly been efficient, and thus has been left alone. " +
      "You can see practically no glitter around here any more, suggesting " +
      "anything that could even remotely count as precious metal will " +
      "most likely not be found further this way.\n");
    return 1;
}


