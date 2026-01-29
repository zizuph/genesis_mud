inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/wild/pass/drow/shop/store"
object ob1;
/* by Antharanos */
void
create_room()
{
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   config_default_trade();
   set_money_greed_sell(95);
   set_money_greed_buy(95);
   set_money_give_max(2400);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_store_room(STORE_ROOM);
   set_short("The General Shop of Undraeth");
   set_long("A darkened, barely lit room of black stone. The walls at the "+
      "far end of the room are covered with numerous weapons and various types "+
      "of armour, along with other more mundane equipment. A large block of "+
      "stone, shaped in a rectangle, blocks your immediate path to the far "+
      "wall. A sign has been placed on the front of the block, no doubt worth reading.\n");
   add_item(({"darkened room","barely lit room","room"}),
      "It is where you are, just look around.\n");
   add_item(({"black stone","stone"}),
      "The dark rock commonly found here within the Dark Dominion.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It has been constructed from the black stone commonly found here within "+
      "the Dark Dominion.\n");
   add_item(({"weapons","armour","mundane equipment","equipment"}),
      "It hangs upon the far wall, well out of your reach.\n");
   add_item(({"large block of stone","large block","block"}),
      "It seems to serve the same purpose as a counter would in any surface "+
      "world shop.\n");
   add_item(({"sign"}),
      "A slab of stone upon which writing has been inscribed.\n");
   add_exit(CPASS(drow/d20),"west","@@msg",-1,-1);
   add_exit(CPASS(drow/shop/store),"up","@@wiz_check",-1,-1);
   ob1 = clone_object(CPASS(drow/npc/shop_owner));
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
   write("The drow scowls at you angrily, grabs you roughly and hurls "+
      "you away from her store room.\n");
   say(QCTNAME(TP) + " tries to go up but is grabbed roughly by the drow and "+
      "hurled back.\n");
   return 1;
}
msg()
{
   write("You leave the building and enter the street.\n");
   say(QCTNAME(TP) + " leaves the building, headed for the street.\n");
   return 0;
}
