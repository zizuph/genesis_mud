/* created by Aridor 02/09/94 */

#include "../local.h"

inherit MININGROOM;

void
create_mining_room()
{
  set_my_long("");
  add_exit(THEIWAR + "r32","north");
  add_exit(THEIWAR + "r29","southwest");
  what1 = "carbon";
  what2 = "iron";
}

void
reset_mining_room()
{
  num1 = random(7);
  num2 = random(5);

}

