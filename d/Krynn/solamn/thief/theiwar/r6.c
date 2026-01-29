/* created by Aridor 03/09/94 */

#include "../local.h"

inherit MININGROOM;


void
create_mining_room()
{
  set_my_long("This is a very fortunate occurrance in the mine. " +
          "Two rather extensive veins, iron and silver cross " +
          "each other here. ");

  add_exit(THEIWAR + "r5", "northeast");
  add_exit(THEIWAR + "r7", "southeast");
  add_exit(THEIWAR + "r8", "southwest");
  add_exit(THEIWAR + "r9", "northwest");

  what1 = "silver";
  what2 = "iron";
}


reset_mining_room()
{
    num1 = random(4);
    num2 = random(6);

}
