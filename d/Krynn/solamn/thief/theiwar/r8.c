/* created by Aridor 03/09/94 */

#include "../local.h"

inherit MININGROOM;

void
create_mining_room()
{
  set_my_long("The silver vein, supposedly going in this direction, is " +
          "very unreliable here, appearing near exhaustion. ");
  add_exit(THEIWAR + "r6", "northeast");
  what1 = "silver";
  what2 = "iron";
}

void
reset_mining_room()
{

    num2 = random(1);
    num2 = random(3);
}


