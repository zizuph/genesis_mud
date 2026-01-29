/*
**   ARGOS - Metro - Pigeon Coop/Shop
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/16/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"
 
object keeper;
 
void reset_room() {
   if (keeper) return;
   keeper=clone_object(NPC_DIR+"pigeon_keeper");
   keeper->equip_me();
   keeper->move(THIS);
   tell_room(THIS,QCNAME(keeper)+" opens his shop for business.\n");
}
 
/* room definition */
void create_room() {
   set_short("A pigeon shop");
   set_long(
       "Stacks of cages line the walls of this dank shop, each with "+
       "a small pigeon nested inside. Unsurprisingly there is no "+
       "furnishing or ornamentation in this shop, only a sign hanging "+
       "by the door. The smell in here makes you think you should "+
       "finish your business here and get out.\n");
 
   add_item(({"building","shop"}),
      "It is just a storage room with cages of pigeons stacked about.\n");
   add_item("pigeons",
      "They are messenger pigeons which can be purchased from the "+
      "keeper. Each is kept in its own cage.\n");
   add_item(({"cage","cages"}),
      "The small cubic cages are made of thin strips of wood, each "+
      "with a small tray with water and food for its inhabitant.\n");
   add_item(({"feather","feathers","quill","quills"}),
           "There seem to be no loose feathers laying around. "+
           "The keeper must be picking them up.\n");
   add_item("sign","It is hanging on the wall. You can read it.\n");
   add_cmd_item("sign","read",
      "It simply reads: Messenger pigeons for sale - 25cc\n");
 
    /* exits */
   add_exit(ROOM_DIR+"proad10","west",0);
   add_exit(ROOM_DIR+"croad8","south",0);
   reset_room();
}
 
int buy(string Parms) {
   object Tp=this_player();
   object Tr=this_object();
   object pigeon;
   string *Parm;
 
   if (!((keeper) && (present(keeper,Tr)))) {
      write("But the keeper isn't here!\n");
      return 1;
   }
 
   if (!(Parms)) { write("Buy what?\n"); return 1; }
   Parm=explode(Parms," ");
 
   if (member_array("pigeon",Parm)==-1) { write("Buy what?\n"); return 1; }
 
   if (MONEY_ADD(Tp,-25)) {
      pigeon=clone_object("/d/Genesis/obj/pigeon");
      pigeon->move(Tp);
      Tp->catch_msg("You buy a messenger pigeon from "+QCTNAME(keeper)+".\n");
      tell_room(Tr,QCTNAME(Tp)+" buys a messenger pigeon from "+
                   QCTNAME(keeper),Tp);
      keeper->command("say Thank you, and have a nice stay in our city.");
      keeper->command("smile");
      }
   else {
      keeper->command("say Seems I can't sell you a pigeon, stranger.");
      keeper->command("smirk");
   }
   return 1;
}
 
void init() {
   ::init();
   add_action("buy","buy");
}
