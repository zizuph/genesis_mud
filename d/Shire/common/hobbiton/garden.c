inherit "/std/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

object dog;

create_room() {
   set_short("small garden");
   set_long(
      "You are in a small garden in front of a tiny cabin. "
    + "There is smoke coming from the chimney of the cabin. "
    + "The garden is well kept and the owner probably spends several "
    + "hours every day pruning the flowers and bushes.\n");

   add_item(({"bush","bushes"}), 
      "The bushes are of several varieties and they all smell like the "
    + "sweetest perfume.\n");

   add_item(({"flower","flowers"}), 
      "They are mostly roses, but here and there you can see a tulip.\n");

   add_prop(ROOM_I_INSIDE,0);
   add_prop(ROOM_M_NO_ATTACK, "The dog won't let you get that close to him, but neither will he let you pass.\n"); /* cant kill dog */

   add_exit(HOBBIT_DIR + "er25","south",0,1);
   add_exit(HOBBIT_DIR + "cabin","enter","@@enter",1);


}

enter_inv(object ob,object from)
{
  ::enter_inv(ob, from);

  if(!dog && living(ob) && !(ob->query_npc()) && !present("corpse")) {
    dog = clone_object(HOBBIT_DIR + "npc/guard_dog");
    dog->move(TO);
  }
}

enter() {
  int sk;
  sk = this_player()->query_skill(SS_SNEAK);

  if(!dog)
    return 0;

  if(sk > 35) {
    write("You manage to sneak by the dog, and into the cabin.\n");
    say(QCTNAME(this_player()) + " manages to pass the dog without being"
	+ " noticed.\n");
    return 0;
  }

  write("The dog will not let you pass.\n");
  say("The dog will not let " + QCTNAME(this_player()) + " pass.\n");

  return 1;
    
}
