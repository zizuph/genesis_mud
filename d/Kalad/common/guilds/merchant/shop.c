inherit "/d/Kalad/room_std";
inherit "/lib/shop";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/caravan/guild/store"
object ob1;
void
create_room()
{
   hear_bell = 1;
   INSIDE;
   config_default_trade();
   set_money_greed_sell(95);
   set_money_greed_buy(95);
   set_money_give_max(2400);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_store_room(STORE_ROOM);
   set_short("The private shop of the Merchants Guild");
   set_long("The private shop of the Merchants Guild of Kabal.\n");
   add_item(({"large sign","sign"}),
      "A large wooden sign hung upon iron nails.\n");
   add_exit(CVAN(guild/hall1),"west",0,-1,-1);
   add_exit(CVAN(guild/store),"east","@@wiz_check",-1,-1);
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
