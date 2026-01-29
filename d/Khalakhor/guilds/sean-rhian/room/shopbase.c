/* Shop Base - base for a simple buy-only shop with an unlimited supply
**             of limited items.
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/10/98     Zima        Created
**
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <money.h>
#include "defs.h"
#include "shopbase.h"
 
object   keeper;              // shop keeper, must be present for transactions
mixed*   item_list=({({})});  // list of items for sale here, see shop.h
 
//
// reset_keeper - clone in the shop keeper
//
public void reset_keeper(string fname) {
   //keeper assumed to be derived NPC of base shopkeeper.c
   if (keeper) return;
   keeper=clone_object(fname);
   keeper->equip_me();
   keeper->move(TO);
   tell_room(TO,QCTNAME(keeper)+" "+(keeper->query_arrive_msg())+".\n");
}
 
//
// query and functions for derived room
//
public object query_keeper()              { return keeper; }
public mixed* query_item_list()           { return item_list; }
public void   set_item_list(mixed* ilist) { item_list = ilist; }
 
//
// room definition
//
public void create_khalakhor_room() {
   set_short("Shop base room");
   set_long(
       "   This is a base room for a shop which allows a player to only "+
       "BUY one of a limited/fixed number of items, with an unlimited "+
       "supply.\n");
}
 
//
// allowed_to_buy - check item minimum buy level with player's SR level
//
int allowed_to_buy(int imbl) {
   //if (imbl < TP->sr_level) return 0; else return 1;
   return 1;
}
 
//
// find_item - matches a string, using parse_command, to an item in the list
//             returns ndx item element if found, -1 if not
//
int find_item(string cmd) {
   int i=0, rc=0;
   if (!stringp(cmd)) return -1;
   while (i < sizeof(item_list)) {
      rc=parse_command(cmd,({(all_inventory(TP))}),(item_list[i][IL_PC_NDX]));
      if (rc) return i; else i++;
   }
   return -1;
}
 
//
// buy - allow a player to buy things here
//
public int buy(string cmd) {
   int    ndx;
   string ishort;
   object item;
 
   // make sure keeper is here
   if (!((keeper) && (present(keeper,TO)))) {
      write("There is no one here to sell you anything.\n");
      return 1;
   }
   if (!cmd) {
      keeper->reply(SKR_BUY_NOT_SPEC);
      return 1;
   }
 
   // determine what player wants to buy, & if he may buy it
   ndx = find_item(cmd);
   if (ndx < 0) {
      keeper->reply(SKR_DONT_HAVE,cmd);
      return 1;
   }
   if (!allowed_to_buy(item_list[ndx][IL_MIN_BUY_LEVEL_NDX])) {
      keeper->reply(SKR_NOT_ALLOWED_TO_SELL,cmd);
      return 1;
   }
 
   // syntax ok, if player has money, sell it to them!
   if (MONEY_ADD(TP,-(item_list[ndx][IL_PRICE_NDX])))
      keeper->complete_sale(item_list[ndx][IL_FNAME_NDX],TP);
   else
      keeper->reply(SKR_SELL_FAIL,cmd);
   return 1;
}
 
//
// ask_price - allows player to ask the shopkeeper for the price of item
//
int  ask_price(string cmd) {
   string item;   // the item in question
   int    ndx;    // ndx of the item in the item list
 
   // make sure keeper is here and question directed to him
   if (!((keeper) && (present(keeper,TO)))) return 0;
   if (!parse_command(cmd,({(all_inventory(TO))}),
       "[of] [the] [a] [an] %s",item))
        return 0;
   ndx=find_item(item);
   if (ndx >= 0)
      keeper->reply(SKR_TELL_PRICE,item,(item_list[ndx][IL_PRICE_NDX]));
   else
      keeper->reply(SKR_DONT_HAVE,item);
   return 1;
}
 
//
// init - add actions
//
public void init() {
   ::init();
   add_action(&buy(), "buy");
   add_action(&ask_price(), "askprice");
}
