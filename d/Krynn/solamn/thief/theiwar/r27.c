/* created by Aridor 02/10/94 */

#include "../local.h"

inherit MININGROOM;

#include RND_MEET

object dwarf;

void
create_mining_room()
{
  set_my_long("Towards the southwest, the cavern leads downwards also. ");
  add_exit(THEIWAR + "r36","southwest","@@downwards");
  add_exit(THEIWAR + "r29","north");
  what1 = "iron";
  what2 = "carbon";
}


void
reset_mining_room()
{
  num1 = random(9);
  num2 = random(7);

  if (dwarf)
    return;
  dwarf = RANDOM_MEET(THEIWARTABLE);
  dwarf->move_living("xxx",TO);
}


int
downwards()
{
    write("The cavern slopes noticeably downwards as you walk to the southwest.\n");
    return 0;
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
