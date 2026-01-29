/*
 *    The raw material shop room for the smiths guild
 *    items needed for forging is bought here
 *    Made 1996 by Morinir for the Shire
 */

#pragma save_binary;

inherit "/d/Shire/room";
inherit "/lib/shop";
inherit "/sys/global/money";

#include "/d/Shire/smiths/smiths.h"
#include "forge.h"
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include <cmdparse.h>

#define SELLER         (FORGE_TANNER)
#define SELLERSAY(s)   seller->command("say "+s)
#define STORE_ROOM     (FORGE_STORE)

#define MAX_PAY 1000    /* Maximum price the owner will pay for something   */
#define MIN_SELL 10     /* Minimum price players will pay for an item       */
#define MAX_MISS 20     /* Maximum % deviation of answer to 'value' command */
#define RIPP_OFF 75     /* % of the value that is added to get sell-value   */
                        /* 100% rippoff means the sellvalue is 100+100%     */

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

void reset_room(); int test_storage();

object seller;

void
create_room() {
   set_short("Raw material shop in Smiths Guild");
   set_long("This room is used by Tobin Ironshoe, a known member of the guild,"+
      " as a shop. Tobin has had this shop for more than forty years"+
      " and some strange and wonderful items are displayed here. It is said"+
      " that this shop has the strangest items for sale, east of Hobbiton,"+
      " but as people from Hobbiton usually say: the shop here has items as"+
      " strange as news from Bree. The only thing that doesn't quite fit into"+
      " this room is a large box with broken items placed in a corner of the"+
      " room. A sign on the wall has instructions that Tobin expect"+
      " people to read before bothering him with stupid questions.\n");
   add_item(({"box","big box","scrap box"}),"This box is filled with broken"+
      " rusted items to be used as raw materials later.\n");
/*
   add_exit(SMITHSDIR_ROOMS+"raw_stor","west","@@test_storage@@");
   add_exit(SMITHSDIR_ROOMS+"master_r","northeast",0);
*/
   add_prop(ROOM_I_INSIDE,1);
   config_default_trade();  /* Set up the trading system */
   set_money_give_max(1000); /* Else things go wrong with "sell all" */
                          /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
   set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
   set_store_room(STORE_ROOM);

   reset_room();
}

init() {
   ::init();

   init_shop();
   add_action("check_value","value");
   add_action("sell","sell");
}

int
test_storage() {
   if (TP->query_wiz_level()) return 0;
   else {
      write("You are not allowed to enter the storage room.\n");
      return 1;
   }
}

void
reset_room()
{
   if (!objectp(seller))
   {
      seteuid(getuid(TO));

      seller = clone_object(SELLER);
      seller->move_living("X", TO);
   }
   else if (ENV(seller) != TO)
   {
      seller->move_living("X", TO);
   }
}

/*
 *  Check if the item player attempts to sell is Smiths Guild related
 *  and if the shop keeper is present
 */

int
shop_hook_allow_sell(object item) {
   if (!present("smiths_guild_keeper")) {
      write("There doesn't seem to be anyone here to buy anything from"+
         " you.\n");
      return 0;
   }

   if (item->query_smiths_item()) return 1;
   if ((item->query_name()=="hide") || (item->query_name()=="skin")) return 1;

   /* The item is not smiths guild related so tonin will not buy it */
   SELLERSAY("I am sorry but I do not deal in such items");
   seller->command("shrug");
   return 0;
}

/*
 *  Check if the shop keeper is present before player may buy
 */

int
shop_hook_allow_buy(object item) {
   if (!present("smiths_guild_keeper")) {
      write("There doesn't seem to be anyone here to sell anything to"+
         " you.\n");
      return 0;
   }
   return 1;
}

/*
 *  Check if the shopkeeper is present before trying to value an object 
 */

int
check_value(string str) {
   if (!present("smiths_guild_keeper")) {
      write("There doesn't seem to be anyone here to value anything for"+
         " you.\n");
      return 1;
   }
   do_value(str);
}

int
sell(string str) {
   object obj;
   object *to_mark;
   int amount=0;

   if (!present("smiths_guild_keeper")) {
      write("There doesn't seem to be anyone here to buy anything from"+
         " you.\n");
      return 1;
   }

   if (!strlen(str))
   {
       return 0;
   }

   if ((!parse_command(str, TP, "[the] %i", to_mark)) ||
      (!sizeof(to_mark = NORMAL_ACCESS(to_mark, 0, 0))))
   {
      return 0;
   }

   if (sizeof(to_mark) != 1)
   {
      return 0;
   }
   else
   {
      obj = to_mark[0];
   }

   if (obj->query_prop(OBJ_I_BROKEN)) {
      amount=obj->query_prop(OBJ_I_WEIGHT)/100;
      amount=amount+10;

      SELLERSAY("I guess I could use your "+obj->short()+" as raw material"+
         " for forging a new item.");
      say(QCTNAME(TP)+" sold "+obj->short()+".\n");
      write("You are payed "+amount+" copper coins.\n");

      tell_room(ENV(TP),QCTNAME(seller)+" drops the "+obj->short()+" in a big"+
         " box labelled scrap.\n");

      obj->remove_object();
      give_money(TP,amount);

      return 1;
   }

   return 0;
}
