inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/wild/pass/dwarf/shop/general_store"
object ob1;
/* by korat */
void
create_room()
{
   config_default_trade();
   set_money_greed_sell(95);
   set_money_greed_buy(95);
   set_money_give_max(0);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   INSIDE;
   set_short("General store");
   set_long("The smell of leather and oil fills your "+
      "nostrils as you look around in this store-room. "+
      "The northern walls are filled with all kinds of "+
      "goods that everyone needs in their homes and on "+
      "their journeys: Lamps, oil-flasks, handy backpack's, "+
      "smaller bags of rough leather and other items.\n"+
      "A large plaque hangs over the counter.\n");
   add_item(({"counter"}),
      "The counter divides this shop in two parts, "+
      "the southern where customers stands and the "+
      "northern where all the goods stands out of reach "+
      "from greedy hands. It seems like the owner has "+
      "had visit from some dewars lately, and learned from the "+
      "experience.\n");
   add_item("plaque","@@plaque");
   add_cmd_item("plaque","read","@@plaque");
   set_noshow_obvious(1);
   add_exit(CPASS(dwarf/shop/m3),"south",0,-1,-1);
   add_exit(CPASS(dwarf/shop/general_store),"north","@@wiz_check",-1,-1);
   set_store_room(STORE_ROOM);
}
plaque()
{
   return "This store only sells items, we do not pay for any items you "+
   "attempt to sell here.\n";
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
   if (TP->query_wiz_level())
      return 0;
   write("An enormous dog jumps out from nowhere and forces you back, it then heads south.\n");
   say(QCTNAME(TP) + " tries to go south but is brutally stopped by a "+
      "massive guard dog, which then heads back south.\n");
   return 1;
}
int
do_read(string str)
{
   return 0;
}
int shop_hook_allow_sell(object ob)
{
   if(ob->id("_Kabal_equip_shop"))return 1;
   return 0;
}
int
do_sell(string str)
{
   TP->catch_msg("This shop only sells equipment.\n");
   return 1;
}
