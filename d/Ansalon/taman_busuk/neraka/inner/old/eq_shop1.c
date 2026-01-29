
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/common/defs.h"

inherit NINROOM;
inherit "/lib/shop";

#include <macros.h>
#define STORE_ROOM    NINNER+"store1.c"

object ob;
void reset_room();

void
create_neraka_room()
{
   config_default_trade();
   set_money_greed_buy(80);
   set_money_greed_sell(75);
   set_short("BLoP's EkWipMent ShoP");
   set_long("You have entered a nice shop filled with weapons and armours "+
   "and other equipment on tables. The ground is covered with animal rugs "+
   "and a small fire burns in a fire pit off by a corner.\n");
      
   add_exit(NINNER+"i16.c","southeast","@@msg@@",0,0);
   add_exit(STORE_ROOM,"west","@@wiz_check");
   
   add_item("sign", "A nice looking sign for you to read.\n");
   add_cmd_item("sign", "read", "@@do_read");
   
   
   set_store_room(STORE_ROOM);
   reset_room();
}
int
msg()
{
    write("You step out of this pawn shop and back into the market "+
    "plaza.\n");
    return 0;
}



void
init()
{
   ::init();   /* You MUST do this in a room-init */
   init_shop(); /* Get the commands from the shop */
}


void
init_shop()
{    
   add_action("do_read", "read");
   add_action("do_list", "list");
   add_action("do_buy", "buy");
   add_action("do_sell", "sell");
   add_action("do_value", "value");
   
}
int
wiz_check()
{
   if (this_player()->query_wiz_level())
      return 0;
   write("Some magic force keeps you from going south.\n");
   say(QCTNAME(this_player()) + " tries to go south but fails.\n");
   return 1;
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NNPC+"goblin_merch");
        ob->move_living("xxx",TO);
    }
}

