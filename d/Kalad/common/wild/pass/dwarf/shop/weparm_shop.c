inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/wild/pass/dwarf/shop/weparm_store"
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
   set_short("The weapon and armour shop in Underhome");
   set_long("The sounds and smells of steel fills this room "+
      "when the shop-keeper goes to deposit bought items and "+
      "fetches them to prospective customers. It dawns upon "+
      "you that this room is dedicated to the merchandising "+
      "of weapons and armours, something that must be a "+
      "lucurative buisness here in Underhome. There is a "+
      "state of war here, if you didn't know. A large sign is "+
      "attached to the wall.\n");
   INSIDE;
   add_item(({"large sign","sign"}),
      "A large wooden sign hung upon iron nails.\n");
   add_exit(CPASS(dwarf/shop/weparm_store),"west","@@wiz_check",-1,-1);
   add_exit(CPASS(dwarf/shop/m3),"east",0,-1,-1);
   
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
   write("A deep dwarf kicks you out of his store-room "+
      "when you try to enter it westwards.\n");
   say(QCTNAME(TP) + " tries to go west but is kicked out by a "+
      "angry deep dwarf.\n");
   return 1;
}
