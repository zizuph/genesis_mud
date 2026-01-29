/*
**   ARGOS - Metro - Glassblower's shop
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/16/95    Zima       Created
**
**   Players can buy glass bottles here, needed when pressing grapes
**      into grapejuice at the Press.
**   Players can buy glass vials here, needed when pressing olives
**      into olive oil at the Press.
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
   keeper=clone_object(NPC_DIR+"glass_blower");
   keeper->equip_me();
   keeper->move(THIS);
   tell_room(THIS,QCNAME(keeper)+" opens his shop for business.\n");
}
 
/* room definition */
void create_room() {
   set_short("A glass shop");
   set_long(
       "Beautiful objects made of hand-blown glass sit on the shelves "+
       "which line the walls of this shop, the crystalline artwork "+
       "refracting colorful light. A large cabinet holds a collection "+
       "of vials and wine bottles, next to which a sign hangs on the "+
       "wall. You think you should be careful not to break anything.\n");
 
   add_item(({"building","shop"}),
      "It a glass shop where hand made glass and crystal objects are "+
      "on display, some of which can be purchased.\n");
   add_item(({"objects","glass","glass objects","statues","animals","people"
      ,"symbols"}),
      "They are small statues of various animals, people and "+
      "symbols made of glass and crystal. You are awed by their beauty.\n");
   add_item(({"walls","shelf","shelves"}),
      "Simple shelves line the four walls of this shop, housing a collection "+
      "of hand-blown glass and crystal artwork.\n");
   add_item("cabinet",
      "It is a tall wooden cabinet holding many small handmade vials and "+
      "empty bottles.\n");
   add_item("vials",
      "They are small vials used to hold oils.\n");
   add_item("bottles",
      "They are hand-blown glass bottles.\n");
   add_item("sign",
      "It is hanging on the wall next to the cabinet. Perhaps you can "+
      "read it.\n");
   add_cmd_item("sign","read",
      "+-------------------------+\n"+
      "| Handmade Glass for Sale |\n"+
      "|                         |\n"+
      "|    Oil vials    - 3cc   |\n"+
      "|    Wine bottles - 6cc   |\n"+
      "|                         |\n"+
      "+-------------------------+\n");
 
   /* exits */
   add_exit(ROOM_DIR+"lroad12","north",0);
   add_exit(ROOM_DIR+"trroad8","east",0);
    reset_room();
}
 
int buy(string Parms) {
   object Tp=this_player();
   object Tr=this_object();
   string *Parm;
   object Obj;
   string ObjName,FileName;
   int    ObjCost=0;
 
   if (!((keeper) && (present(keeper,Tr)))) {
      write("But the shop keeper isn't here!\n");
      return 1;
   }
 
   if (!(Parms)) { write("Buy what?\n"); return 1; }
   Parm=explode(Parms," ");
 
   if (member_array("bottle",Parm) > -1) {
      ObjName="glass wine bottle";
      FileName="glass_bottle";
      ObjCost= -6;
      }
   if (member_array("vial",Parm) > -1) {
      ObjName="small glass vial";
      FileName="glass_vial";
      ObjCost= -3;
      }
   if (!(ObjCost)) {
      keeper->command("say I only sell bottles and vials to outsiders now.");
      return 1;
   }
 
   if (MONEY_ADD(Tp,ObjCost)) {
      Obj=clone_object((OBJ_DIR+FileName));
      Obj->move(Tp);
      Tp->catch_msg("You buy a "+ObjName+" from "+QTNAME(keeper)+".\n");
      tell_room(Tr,QCTNAME(Tp)+" buys a "+ObjName+" from "+
                   QTNAME(keeper)+".\n",Tp);
      keeper->command("say Thank you, and have a nice stay in our city.");
      keeper->command("smile");
      }
   else {
      keeper->command("say Seems I can't sell to you, stranger."+
                      " Are you sure you have enough money?");
      keeper->command("smirk");
   }
   return 1;
}
 
void init() {
   ::init();
   add_action("buy","buy");
}
