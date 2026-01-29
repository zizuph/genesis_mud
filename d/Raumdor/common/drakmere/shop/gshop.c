#include "defs.h"
inherit STD_ROOM;
inherit "/d/Raumdor/std/shop_list";
#define STORE_ROOM "/d/Raumdor/common/drakmere/shop/store"
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
   set_money_give_max(1000);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_store_room(STORE_ROOM);
   set_short("The Drakmere General Store");
   set_long("This is the general store of Drakmere. Its "+
   "and old stone and wood construction, fairly strong. A fire burns "+
   "in a fireplace to the east of you. Along the walls you see various "+
   "weapons and armours hanging. Behind a large wooden counter, stands "+
   "a merchant, ready to help you.\n");
   add_item(({"large sign","sign"}),
      "A large wooden sign hung upon iron nails.\n");
   add_exit(DRAKMERE_SHOP_DIR + "store", "east", "@@wiz_check");
   add_exit(DRAKMERE_DIR + "road17", "northwest",0);
   add_exit(DRAKMERE_DIR + "road18","north",0);
   ob1 = clone_object(DRAKMERE_NPC_DIR + "gs_owner.c");
   ob1 -> move_living("xxx", TO);
   
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
   write("The old man scowls at you, grabs you by the ear and pushes "+
      "you away from his store room.\n");
   say(QCTNAME(TP) + " tries to go west but is grabbed by the ear and "+
      "unceremoniously pushed back by the old man.\n");
   return 1;
}

int *
query_coordinates()
{
    return ({68, 1, 0});
}
