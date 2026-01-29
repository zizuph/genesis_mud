/* ARGOS - SWTERR - Dirt road along south bank of river
**
** History:
** Date      Coder      Action
** --------- ---------- --------------------------------
** 1/12/93   Zima       Created
** 9/10/95   Zima       Travelling Merchant moved here
**
*/
/* inherits/includes */
inherit "/std/room";
inherit  "/lib/shop";
#include <stdproperties.h>
#include <macros.h>
#define  STORE_ROOM (ROOM_DIR + "wagonrm")  /* Where the items are stored */
#include "defs.h"
 
object merchant=0;
object wagon=0;
 
void reset_room() {
    if (merchant) return;
    merchant=clone_object(NPC_DIR+"merchant");
    merchant->move(THIS);
    tell_room(THIS, QCNAME(merchant)+" emerges from the old wagon.\n");
}
 
void create_room() {
   set_short("A dirt road along a river");
   set_long(
      "You walk along a dirt road which follows the " +
      "southern bank of a rushing river. A dark forest lines the " +
      "south side of the road, filled with dark trees. The road " +
      "continues to the west, and bends along the river to the "   +
      "northeast. You hear the evil caw of some bird from the forest, "+
      "into which you see an entrance to the southwest.\n");
 
   add_item("road",
      "A simple dirt road, newly cleared through the forest, which " +
      "follows a river along its southern bank.\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. " +
      "The forest on the other side of the river is filled with oaks and " +
      "maples.\n");
   add_item(({"forest","trees"}),
       "Dark mohagany trees, many overgrown with vines, grow densely " +
       "around you, their thick canopy making a dark shade on the forest " +
       "floor.\n");
 
   config_default_trade();
   wagon=clone_object(OBJ_DIR+"wagon");
   wagon->move(THIS);
   set_store_room(STORE_ROOM);
   reset_room();
 
   /* exits */
   add_exit(ROOM_DIR+"r21","west",0);
   add_exit(ROOM_DIR+"r23","northeast",0);
   add_exit(ROOM_DIR+"for7","southwest",0);
}
 
void init() {
    ::init();   /* You MUST do this in a room-init */
    init_shop();
}
 
int do_buy(string args) {
  /* prevents buy command if merchant isn't present */
  int buyrc;
  if (merchant && present(merchant,this_object())) {
      buyrc = ::do_buy(args);
     if (buyrc) { /* transaction went OK */
        merchant->say_random_thanks();
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
 
int do_sell(string args) { /* prevents selling when merchant not present */
  int sellrc;
  if (merchant && present(merchant,this_object())) {
     sellrc = ::do_sell(args);
     if (sellrc) { /* transaction ok */
        merchant->say_random_thanks();
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
