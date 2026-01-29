inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/trade/tsquare/jewel_store"
object ob1;
void
create_room()
{
   config_default_trade();
   set_money_greed_sell(95);
   set_money_give_max(1000);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   hear_bell = 1;
   INSIDE;
   set_short("Xavier's Jewel Shop");
   set_long("This is Xavier's jewel shop. Xavier sells the finest gems "
      +"in all of Kabal. His jewels are mined in the mountains north of Kabal. "
      +"You might want to buy a jewel to give to your beloved.\n");
   add_exit(TRADE(tsquare/t9),"west");
   add_exit(TRADE(tsquare/jewel_store),"south","@@wiz_check");
   set_store_room(STORE_ROOM);
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
   write("You can't go in there scumbag, get lost!\n");
   say(QCTNAME(TP) + " tries to go south, buy gets kicked in the groin by a "
      +"large man with a big axe.\n");
   return 1;
}
int shop_hook_allow_sell(object ob)
{
   if(ob->id("_kalad_jewel_shop_"))return 1;
   return 0;
}
int
do_sell(string str)
{
   TP->catch_msg("We don't want that crap here! Get out!\n");
   return 1;
}

int
do_read(string str)
{
   return 0;
}
