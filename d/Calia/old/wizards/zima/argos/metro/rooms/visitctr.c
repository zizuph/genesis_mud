/*
**  ARGOS - Metro - Visitors Center
**  A player can solve a tour here by signing the registry/guest book.
**  The noblewoman is here to give hints to the questor.
**  - get tour from Alexis in the park
**  - get quill from Bursar in the bank
**  - come here
**  - dip quill in ink
**  - sign registry
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       3/5/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "../tours.h"
 
object nobleman=0;
object pedestal=0;
int    NumBach=0;
int    NumOuzo=0;
#include "visitctr.ext"
 
void reset_room() {
   object Tr=this_object();
   if (!nobleman) {
      nobleman=clone_object(NPC_DIR+"vcnoble");
      nobleman->equip_me();
      nobleman->move(Tr);
      tell_room(Tr,QCTNAME(nobleman)+" enters from the street.\n");
   }
   if (!(pedestal)) {
      pedestal=clone_object(OBJ_DIR+"vcpedestal");
      pedestal->move(Tr);
      tell_room(Tr,QCTNAME(nobleman)+" places a pedestal on the floor.\n");
   }
   NumBach=6;
   NumOuzo=4;
   tell_room(Tr,QCTNAME(nobleman)+" places some refreshments on the tray.\n");
}
 
create_room() {
   set_short("Visitors Center of Argos");
   set_long(
      "This newly renovated building has been transformed into a "+
      "welcome center for those who are visiting the city. A silver "+
      "tray sits in the corner of the room on a stand, while a banner "+
      "hangs on the eastern wall. A pedestal sits next to the doorway "+
      "which leads into the back room of the center to the south.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("banner",
            "It is a banner of blue silk embroidered with the royal "+
            "arms of Argos, a shield emblazoned with a rampant winged "+
            "horse surmounted by a crown with three jewels.\n");
   add_item(({"book","registry"}),
            "It is a registration book where outsiders may register "+
            "their visit for posterity's sake. It is sitting open "+
            "on top of the pedestal next to a bottle of ink. To "+
            "read it, try 'read registry'.\n");
   add_cmd_item("registry","read","@@read_book");
 
   add_item(({"ink","bottle","bottle of ink"}),
            "It is a small ceramic bottle with black ink. A quill can "+
            "be dipped in it to sign the registry.\n");
   add_item("tray","@@exa_tray");
   add_item(({"bachlava","bachlavas","piece of bachlava",
              "pieces of bachlava"}), "@@exa_bachlava");
   add_item(({"ouzo","ouzos"}), "@@exa_ouzo");
   add_item("stand","A small table with a silver serving tray on top.\n");
 
 
   add_item("doorway","It leads south to the backroom of the center "+
                      "where the public bulletin board can be found.\n");
   add_exit(ROOM_DIR+"lroad8", "north", 0);
   add_exit(ROOM_DIR+"boardrm","south", 0);
   add_exit(ROOM_DIR+"proad8", "west",  0);
   reset_room();
}
 
/************************ Tray of food functions **********************/
string DescBach(int Num) {
   if (Num==1) return "a piece of bachlava";
   else        return (Num+" pieces of bachlava");
}
 
string DescOuzo(int Num) {
   if (Num==1) return "an ouzo";
   else        return Num+" ouzos";
}

string exa_tray() {
   string desc="It is a silver serving tray";
 
   if (NumBach==0)
      if (NumOuzo==0)
         return (desc+" with nothing but a few crumbs on it.\n");
      else
         return (desc+" with "+(DescOuzo(NumOuzo))+" on it.\n");
   else
      if (NumOuzo==0)
         return (desc+" with "+DescBach(NumBach)+" on it.\n");
      else
         return (desc+" with "+(DescBach(NumBach))+" and "+
                (DescOuzo(NumOuzo))+" on it.\n");
}
 
 
string exa_bachlava() {
   if (NumBach) return
      "Bachlava is a sweet pastry made with fruit, "+
      "a favorite treat for the people of this area. No one is looking, "+
      "perhaps you could take one from the tray.\n";
   else return
      "There are only a few crumbs left on the tray, it is all gone.\n";
}
 
string exa_ouzo() {
   if (NumOuzo) return
      "Ouzo is a flavored alcoholic beverage, "+
      "a favorite drink for the people of this area. No one is looking, "+
      "perhaps you could take one from the tray.\n";
   else return
      "The ouzos on the tray are all taken now.\n";
}
 
void init() {
   ::init();
   add_action("take","get");
   add_action("take","take");
   add_action("dip","dip");
   add_action("sign","sign");
}
