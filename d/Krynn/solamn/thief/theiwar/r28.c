/* created by Aridor 03/09/94 */

#include "../local.h"

inherit MININGROOM;

#include RND_MEET
#include <macros.h>

object dwarf;
string* warned = ({});

void
create_mining_room()
{
  set_my_long("The continuation of the iron ore mine has not been exhausted yet. " +
          "You can see very recent traces, as well as fragments, stones and " +
          "debris lying on the floor. The mine leads back down to the southeast. ");

  add_exit(THEIWAR + "r9", "southeast");
  what1 = "iron";
  what2 = "silver";

  add_item(({"fragments","debris","stones"}),
       "You recognize these stones as worthless, and decide to leave them where they are.\n");
  add_cmd_item(({"fragments","debris","stones"}),({"get","take","pick"}),
           "You recognize these stones as worthless, and leave them where they are.\n");


}

void
reset_mining_room()
{
    num1 = random(7);
    num2 = random(4);


    if (dwarf)
      return;
    seteuid(getuid(TO));
    dwarf = RANDOM_MEET(THEIWARTABLE);
    dwarf->move_living("xxx",TO);
    warned = ({});
}

int
hook_mining_now(object who)
{
    if (!dwarf || E(dwarf) != TO)
      return 0;
    if (member_array(TP->query_real_name(),warned) == -1)
      {
      dwarf->command("emote rumbles: Leave THAT alone, will ya!!");
      dwarf->command("glare angrily");
      write("You jump back and decide not to continue mining.\n");
      warned += ({ TP->query_real_name() });
      }
    else
      {
      dwarf->command("say I warned you!");
      write(dwarf->query_The_name(TP) + " attacks you!\n");
      dwarf->attack_object(who);
      }
    return 1;
}
