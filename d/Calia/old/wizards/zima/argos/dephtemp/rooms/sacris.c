/*
**  Temple of Dephonia - Sacristry, place of the Holy items
**
** This is where a player on the vision quest gets the quest items needed
**     if he/she meets the proper conditions:
**     Medallion: must be wearing robe (armours/visrobe)
**     Dagger:    must be wearing robe, medallion and be "blessed"
**                (have invisible object objects/visbless)
**     Bowl:      must be wearing robe, medallion and have corpse
**                of lamb (nwterr/objects/lambbody)
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"
 
/* Quest objects here at load, do NOT reappear at reset */
int dagger_here = 1;
int bowl_here   = 1;
int medal_here  = 1;
 
object sacristan=0;
void
return_object(int ObjNum) {
   switch (ObjNum) {
      case 0: medal_here=1;  break;
      case 1: dagger_here=1;  break;
      case 2: bowl_here=1;    break;
   }
}
 
void
reset_room()
{
    if (sacristan) return;
    sacristan=clone_object(NPC_DIR+"sacristn");
    sacristan->equip_me();
    sacristan->move(THIS);
    tell_room(THIS, QCTNAME(sacristan)+" walks in.\n");
}
 
create_room() {
   set_short("The Sacristry of the Temple of Dephonia");
   set_long(break_string(
      "The sweet aroma of incense overcomes you as you walk into "+
      "this large triangular chamber, the sweet smell rising from "+
      "a burner which sits atop a triangular table in the center "+
      "of the room. Three pedestals sit in each corner of the "+
      "chamber, covered with silk cloths. You get the strange "+
      "feeling of a powerful presence in this place.\n",70));
 
   add_item("incense","It is rising from the burner on the table.\n");
   add_item("burner","It is a golden globe with holes in the top "+
                     "from which the incense is streaming.\n");
   add_item("table","It is actually a tall triangular block of " +
            "black marble, more like an altar of some sort. "+
            "The incense burner is sitting on it.\n");
   add_item(({"pedestals","pedestal"}),
      "Three pedestals sit in each of the northern, southeastern "+
      "and southwestern corners of the triangular chamber, covered "+
      "with silk cloths. Perhaps you should take a closer look "+
      "at each one of them, the first, second and third.\n");
   add_item("cloths","Fine silk cloths cover each of the pedestals.\n");
 
   add_item("first pedestal","@@exa_pedestal1");
   add_item("second pedestal","@@exa_pedestal2");
   add_item("third pedestal","@@exa_pedestal3");
 
   add_item(({"dagger","ceremonial dagger"}), "@@exa_dagger");
   add_item("bowl","@@exa_bowl");
   add_item(({"medallion","gold medallion"}), "@@exa_medal");
 
   add_item(({"medallion from pedestal","gold medallion from pedestal",
      "medallion from the pedestal","gold medallion from the pedestal",
      "medallion from first pedestal","gold medallion from first pedestal",
      "medallion from the first pedestal",
       "gold medallion from the first pedestal"}), "@@exa_medal");
   add_cmd_item(({"medallion from pedestal","gold medallion from pedestal",
      "medallion from the pedestal","gold medallion from the pedestal",
      "medallion from first pedestal","gold medallion from first pedestal",
      "medallion from the first pedestal",
      "gold medallion from the first pedestal"}),({"take","get"}),
      "@@take_medal");
 
   add_item(({"dagger from pedestal","ceremonial dagger from pedestal",
      "dagger from the pedestal","ceremonial dagger from the pedestal",
      "dagger from second pedestal","ceremonial dagger from second pedestal",
      "dagger from the second pedestal",
      "ceremonial dagger from the second pedestal"}), "@@exa_dagger");
   add_cmd_item(({"dagger from pedestal","ceremonial dagger from pedestal",
      "dagger from the pedestal","ceremonial dagger from the pedestal",
      "dagger from second pedestal","ceremonial dagger from second pedestal",
      "dagger from the second pedestal",
      "ceremonial dagger from the second pedestal"}),({"take","get"}),
      "@@take_dagger");
 
   add_item(({"bowl from pedestal","silver bowl from pedestal",
      "bowl from the pedestal","silver bowl from the pedestal",
      "bowl from third pedestal","silver bowl from third pedestal",
      "bowl from the third pedestal",
      "silver bowl from the third pedestal"}), "@@exa_bowl");
   add_cmd_item(({"bowl from pedestal","silver bowl from pedestal",
      "bowl from the pedestal","silver bowl from the pedestal",
      "bowl from third pedestal","silver bowl from third pedestal",
      "bowl from the third pedestal",
      "silver bowl from the third pedestal"}),({"take","get"}),
      "@@take_bowl");
 
   add_cmd_item(({"dagger","ceremonial dagger","bowl","medallion",
      "gold medallion"}), ({"get","take"}), "Take what from what?\n");
 
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"sanct","south",0);
   reset_room();
}
 
string exa_pedestal1() {
   string desc;
   desc= "The pedestal in the southwestern corner is covered with " +
         "a black silk cloth embroidered with gold ravens on "  +
         "the corners. ";
   if (medal_here) desc = desc + "There is a gold medallion placed on it.\n";
   else            desc = desc + "\n";
   return desc;
}
 
string exa_pedestal2() {
   string desc;
   desc= "The pedestal in the northern corner is covered with " +
         "a silver silk cloth embroidered with black ravens on "  +
         "the corners. ";
   if (dagger_here) desc=desc+"There is a ceremonial dagger placed on it.\n";
   else             desc=desc+"\n";
   return desc;
}
 
string exa_pedestal3() {
   string desc;
   desc= "The pedestal in the northern corner is covered with " +
         "a red silk cloth embroidered with black ravens on "  +
         "the corners. ";
   if (bowl_here) desc=desc+"There is a silver bowl placed on it.\n";
   else           desc=desc+"\n";
   return desc;
}
 
int take_medal() {
   object medal = 0;
   object TPlay = this_player();
   object TRoom = environment(TPlay);
 
   if (medal_here) { /* medal must be here */
      if ((TPlay->query_armour(A_BODY))->id(VDQ_ROBE)) { /* must wear robe */
         medal=clone_object(ARMOUR_DIR+"vismedal");
         medal->move(TPlay);
         write("You take the gold medallion from the first pedestal.\n");
         tell_room(TRoom, QCNAME(TPlay)+" takes a gold medallion from the "+
                   "first pedestal.\n", TPlay);
         if (sacristan) sacristan->command("emote smiles mysteriously.");
         medal_here=0;
         }
      else {
         write("The gold medallion burns your hand and you jerk back!\n");
         tell_room(TRoom,QCNAME(TPlay)+" touches the gold medallion on the "+
                   "first pedestal then suddenly jumps back!\n",TPlay);
         if (sacristan) {
            sacristan->command(
               "say You are not shrouded in chosen darkness, aspirant.");
            sacristan->command("emote smiles mysteriously.");
         }
      }
      }
   else {
      write("You find no medallion here.\n");
      if (sacristan) sacristan->command("emote stares suspiciously.");
   }
   return 1;
}
 
int take_dagger() {
   object dagger = 0;
   object TPlay  = this_player();
   object TRoom  = environment(TPlay);
 
   if (dagger_here) { /* dagger must be here */
      if (((TPlay->query_armour(A_BODY))->id(VDQ_ROBE))  && /* wears robe */
          ((TPlay->query_armour(A_NECK))->id(VDQ_MEDAL)) && /* wears medal*/
          (present(VDQ_BLESSING,TPlay)))                    /* is blessed */
         {
         dagger=clone_object(WEAPON_DIR+"visdaggr");
         dagger->move(TPlay);
         write("You take the ceremonial dagger from the second pedestal.\n");
         tell_room(TRoom, QCNAME(TPlay)+" takes a ceremonial dagger from "+
                   "the second pedestal.\n",TPlay);
         if (sacristan) sacristan->command("emote smiles mysteriously.");
         dagger_here=0;
         }
      else {
         write("The ceremonial dagger burns your hand and you jerk back!\n");
         tell_room(TRoom,QCTNAME(TPlay)+" touches the ceremonial dagger on "+
                   "the second pedestal then suddenly jumps back!\n",TPlay);
         if (sacristan) {
            sacristan->command(
               "say You are not yet ready for that, aspirant.");
            sacristan->command("emote smiles mysteriously.");
         }
      }
      }
   else {
      write("You find no dagger here.\n");
      if (sacristan) sacristan->command("emote stares suspiciously.");
   }
   return 1;
}
 
int take_bowl() {
   object bowl   = 0;
   object TPlay  = this_player();
   object TRoom  = environment(TPlay);
 
   if (bowl_here) { /* bowl must be here */
      if (((TPlay->query_armour(A_BODY))->id(VDQ_ROBE))  && /* wears robe */
          ((TPlay->query_armour(A_NECK))->id(VDQ_MEDAL)) && /* wears medal*/
           (present(VDQ_LAMBCORPSE,TPlay)))                  /* has corpse */
         {
         bowl=clone_object(OBJ_DIR+"visbowl");
         bowl->move(TPlay);
         write("You take the silver bowl from the third pedestal.\n");
         tell_room(TRoom, QCNAME(TPlay)+" takes a silver bowl from "+
                   "the third pedestal.\n",TPlay);
         if (sacristan) sacristan->command("emote smiles mysteriously.");
         bowl_here=0;
         }
      else {
         write("The silver bowl burns your hand and you jerk back!\n");
         tell_room(TRoom,QCNAME(TPlay)+" touches the silver bowl on the "+
                   "third pedestal then suddenly jumps back!\n",TPlay);
         if (sacristan) {
            sacristan->command(
               "say You are not yet ready for that, aspirant.");
            sacristan->command("emote smiles mysteriously.");
         }
      }
      }
   else {
      write("You find no bowl here.\n");
      if (sacristan) sacristan->command("emote stares suspiciously.");
   }
   return 1;
}
string exa_medal() {
   if (medal_here)
      return "The gold medallion is laying on the first pedestal.\n";
   else
      return "You see no medallion here.\n";
}
 
string exa_dagger() {
   if (dagger_here)
      return "The ceremonial dagger is laying on the second pedestal.\n";
   else
      return "You see no dagger here.\n";
}
 
string exa_bowl() {
   if (bowl_here)
      return "The silver bowl is laying on the third pedestal.\n";
   else
      return "You see no bowl here.\n";
}
