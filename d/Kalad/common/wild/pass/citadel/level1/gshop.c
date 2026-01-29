inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/caravan/shop/store"
object ob1;
/* by Antharanos with help from Vladimir */
void
create_room()
{
   config_default_trade();
   set_money_greed_sell(95);
   set_money_greed_buy(95);
   set_money_give_max(1000);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_store_room(STORE_ROOM);
   set_short("The Kabal general store");
   set_long("This is the general store of the Caravan district, peering "+
      "ahead of you, you can see a large wooden counter behind which sits "+
      "the shopkeeper, Anthios. Behind him you can see racks filled with "+
      "all manner of goods, brought here by travelling merchants or the "+
      "occasional adventurer. A large sign hangs over the counter.\n");
   INSIDE;
   hear_bell = 1;
   add_item(({"large sign","sign"}),
      "A large wooden sign hung upon iron nails.\n");
   add_exit("/d/Kalad/common/caravan/shop/store", "west", "@@wiz_check",-1,-1);
   add_exit("/d/Kalad/common/caravan/caravan/s3", "east",0,-1,-1);
   ob1 = clone_object("/d/Kalad/common/caravan/npc/gsowner");
   ob1 -> move_living("xxx", TO);
   
   INSIDE;
}
void
init()
{
   ::init();
   init_shop();
}
int
wiz_check()
{
   if(TP->query_wiz_level())
      return 0;
   write("The half-elf scowls at you, grabs you by the ear and pushes "+
      "you away from his store room.\n");
   say(QCTNAME(TP) + " tries to go west but is grabbed by the ear and "+
      "unceremoniously pushed back by the half-elf.\n");
   return 1;
}
