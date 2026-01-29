/* created by Aridor 03/09/94 */

#include "../local.h"

inherit MININGROOM;

#include RND_MEET

object dwarf;

void
create_mining_room()
{
  set_my_long("The continuation of the iron ore mine apparently did prove " +
          "successful in this direction. The hallway leads upwards, but " +
          "still runs into a mainly northwestern direction. ");
  add_exit(THEIWAR + "r28", "northwest");
  add_exit(THEIWAR + "r6", "southeast");
  what1 = "iron";
  what2 = "carbon";

}

void
reset_mining_room()
{
    num1 = random(7);
    num2 = random(2);

    if (dwarf)
      return;
    dwarf = RANDOM_MEET(THEIWARTABLE);
    dwarf->move_living("xxx",TO);
}


