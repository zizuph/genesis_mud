/*
** ARGOS - Metro - shop (Katasema's Emporium)
**
** History
** Date      Coder      Action
** -------- ----------- --------------------------
** 3/3/95   Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
inherit "/lib/shop";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  STORE_ROOM (ROOM_DIR + "shoprm")  /* Where the items are stored */
object merchant=0;
 
void reset_room() {
    if (merchant) return;
    merchant=clone_object(NPC_DIR+"merchant");
    merchant->equip_me();
    merchant->move(THIS);
    tell_room(THIS, QCTNAME(merchant)+" opens his shop for business.\n");
}
 
/* room definition */
void create_room() {
   config_default_trade();
   set_short("Katasemas Emporium");
   set_long(
       "You are standing in Katasemas Emporium, a shop where the public "+
       "and visitors come to buy and sell various wares. Several boxes, "+
       "crates and wardrobes stand along the walls of the establishment "+
       "in a neat if unornate fashion. There is a sign hanging on the "+
       "the wall.\n");
 
   set_store_room(STORE_ROOM);
 
   add_item("sign",
      "It is a simple wood sign hanging on the wall. It has " +
      "writing on it.\n");
   add_item(({"boxes","crates","wardrobes"}),
      "They are situated around you along the walls of the shop, full "+
      "of the bargains that Katasemas offers.\n");
   add_cmd_item(({"boxes","crates","wardrobes"}), ({"open","unlock","take"}),
      "If you want to see what Katasemas has to offer, type 'list'.\n");
 
    /* exits */
   add_exit(ROOM_DIR+"droad9","east",0);
   reset_room();
}
 
void init() {
    ::init();
    init_shop();  /* initialize standard shop functions */
}
 
string random_thanks() {
   /* random thank you message merchant says at each transaction */
   string *randthanks;
   randthanks = ({
                "It is a pleasure dealing with me, yes?",
                "And may the Tritheon bring you great wealth.",
                "A mutually beneficial transaction, no?",
                "You have gotten a bargain, no?",
                "Perhaps you will come again, yes?",
                "You have a deal, though I shall lose money on this one.",
                "You have something else, yes?"
                });
   return randthanks[random(sizeof(randthanks))];
}
 
int do_buy(string args) {
  /* prevents buy command if merchant isn't present */
  int buyrc;
  if (merchant && present(merchant,this_object())) {
      buyrc = ::do_buy(args);
     if (buyrc) { /* transaction went OK */
        merchant->command("say " + random_thanks());
        merchant->command("smile greedily");
        }
     else
        merchant->command("say what do you mean by this?");
     return buyrc;
     }
  else {
     tell_object(this_player(),"But the merchant is not here!\n");
     return 1;
  }
}
 
int do_sell(string args) {
  /* prevents selling when merchant not present */
  int sellrc;
  if (merchant && present(merchant,this_object())) {
     sellrc = ::do_sell(args);
     if (sellrc) { /* transaction ok */
        merchant->command("say " + random_thanks());
        merchant->command("smile greedily");
     }
     else
        merchant->command("say what do you mean by this?");
     return sellrc;
    }
  else {
     tell_object(this_player(),"But the merchant is not here!\n");
     return 1;
  }
}
