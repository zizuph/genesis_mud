/*
**   ARGOS - Metro - Brass smiths shop
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/95    Zima       Created
**
**   Players can buy brass lamps here. Lamps need oil to be used,
**      which is obtained by picking olives in the olive grove
**      (swterr/rooms/ogrove*), buying an empty vial (rooms/glasswrk),
**      pressing the olives into oil into the vial (rooms/press), and
**      then filling the lamp with oil (objects/vial)
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
   keeper=clone_object(NPC_DIR+"brassman");
   keeper->equip_me();
   keeper->move(THIS);
   tell_room(THIS,QCNAME(keeper)+" opens his shop for business.\n");
}
 
/* room definition */
void create_room() {
   set_short("A brass shop");
   set_long(
       "Coppery objects made of molded brass sit on the shelves "+
       "which line the walls of this shop, the shiny artwork "+
       "glistening in the light. A large cabinet holds a collection "+
       "of brass lamps, next to which a sign hangs on the wall. "+
       "You wonder at the patience one must have to make such things.\n");
 
   add_item(({"building","shop"}),
      "It a brass shop where hand made objects of brass and other "+
      "precious metals are on display, some of which can be purchased.\n");
   add_item(({"objects","brass","brass objects","rings","jewelry",
      "statuettes","art","artwork"}),
      "Many different objects fashioned from brass sit on the shelves, "+
      "including jewlery, lamps and statuettes. You are awed by their "+
      "beauty.\n");
   add_item(({"walls","shelf","shelves"}),
      "Simple shelves line the four walls of this shop, housing a collection "+
      "of hand-made brass artwork.\n");
   add_item("cabinet",
      "It is a tall wooden cabinet holding many brass lamps which are for "+
      "sale.\n");
   add_item("sign",
      "It is hanging on the wall next to the cabinet. Perhaps you can "+
      "read it.\n");
   add_cmd_item("sign","read",
      "+-------------------------+\n"+
      "| Brass Artwork for Sale  |\n"+
      "|                         |\n"+
      "|  - Lamps        75cc    |\n"+
      "|  - Sheep shears 15cc    |\n"+
      "+-------------------------+\n");
 
   /* exits */
   add_exit(ROOM_DIR+"lroad14","north",0);
   add_exit(ROOM_DIR+"trroad8","west",0);
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
 
   if (member_array("lamp",Parm) > -1) {
      ObjName="brass lamp";
      FileName="brass_lamp";
      keeper->command("say You'll need a vial of olive oil to fuel that.");
      ObjCost= -75;
   }
   else if (member_array("shears",Parm) > -1) {
      ObjName="set of sheep shears";
      FileName="sheep_shears";
      keeper->command("say You don't have to kill the sheep to shear it, "+
                      "you know.");
      ObjCost= -15;
   }
   if (!(ObjCost)) {
      keeper->command("say I only sell what's listed on the sign.\n");
      return 1;
   }
 
   if (MONEY_ADD(Tp,ObjCost)) {
      Obj=clone_object((OBJ_DIR+FileName));
      Obj->move(Tp);
      Tp->catch_msg("You buy a "+ObjName+" from "+QTNAME(keeper)+".\n");
      tell_room(Tr,QCTNAME(Tp)+" buys a "+ObjName+" from "+
                   QTNAME(keeper)+".\n",Tp);
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
