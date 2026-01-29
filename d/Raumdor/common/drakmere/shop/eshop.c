#include "defs.h"
inherit STD_ROOM;
inherit "/d/Raumdor/std/shop_list";
#define STORE_ROOM "/d/Raumdor/common/drakmere/shop/estore"

object ob1;

/* by Sarr */

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
   config_default_trade();
   set_money_greed_sell(95);
   set_money_greed_buy(95);
   set_money_give_max(0);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_short("Equipment Store");
   set_long("You've entered a medium-sized stone and wood building. "+
   "A wooden table with lamps, flasks, torches and other equipment "+
   "stand near the back of the room, where a merchant stands ready "+
   "to assist you.\n");
   add_item("table","Made of strong oak wood.\n");
   add_item("plaque","@@plaque");
   add_cmd_item("plaque","read","@@plaque");
   add_exit(DRAKMERE_DIR + "road17","southwest",0);
   add_exit(DRAKMERE_SHOP_DIR + "estore","east","@@wiz_check");
   add_exit(DRAKMERE_DIR + "road18","south",0);
   set_store_room(STORE_ROOM);
   ob1 = clone_object("/d/Raumdor/common/drakmere/npc/es_owner");
   ob1 -> move_living("xxx", TO);
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

int *
query_coordinates()
{
    return ({68, 3, 0});
}
