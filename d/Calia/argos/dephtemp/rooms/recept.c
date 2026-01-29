/*
**  Temple of Dephonia, Reception/Conference chamber
**  A meeting of "rebel allies" is beginning to form in this room,
**    thus the presence of a Kretan and an Argosian nobleman
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/94    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "vqscenes.h"
#define  SCENE_NUM 9
 
object nobleman=0;
object kretan=0;
object priestess=0;
int    BachHere=1;
int    OuzoHere=1;
 
void
reset_room()
{
   if (!nobleman) {
      nobleman=clone_object(NPC_DIR+"recnoble");
      nobleman->equip_me();
      nobleman->move(THIS);
      tell_room(THIS,QCNAME(nobleman)+" enters from the corridor.\n");
   }
   if (!kretan) {
      kretan=clone_object(NPC_DIR+"reckretn");
      kretan->equip_me();
      kretan->move(THIS);
      tell_room(THIS,QCNAME(kretan)+" enters from the corridor.\n");
   }
   if (!priestess) {
      priestess=clone_object(NPC_DIR+"recprsts");
      priestess->equip_me();
      priestess->move(THIS);
      tell_room(THIS,QCNAME(priestess)+" enters from the corridor.\n");
   }
   tell_room(THIS,"A servant girl scampers in with a new tray of "+
                  "food and hurries out.\n");
   BachHere=1;
   OuzoHere=1;
}
 
create_room() {
   set_short("Reception Chamber in the Temple of Dephonia");
   set_long(
      "You walk into a plush chamber furnished with a long mohogany "+
      "table surrounded by eight high-backed cushioned chairs, "+
      "obviously a conference room of some sort. There is a silver "+
      "tray sitting on a stand next to the doorway, and a long " +
      "tapestry adorns the northeastern wall of the rectangular " +
      "room. The doorway leads west into the corridor.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("table",
      "It is a long rectangular conference table, made of polished " +
      "antique mohagany, supported by two pedestal supports on " +
       "either end.\n");
   add_item(({"chair","chairs"}),
      "Made of the same antique mohagany as the table, the eight "+
      "chairs are cushioned on the seat and on their high backs " +
      "with red silk embroidered with black ravens.\n");
 
   add_item("tray","@@exa_tray");
   add_item(({"bachlava","bachlavas","piece of bachlava",
              "pieces of bachlava"}), "@@exa_bachlava");
   add_item(({"ouzo","ouzos"}), "@@exa_ouzo");
   add_item("stand","A small table with a silver serving tray on top.\n");
 
   add_item("tapestry",
      "The woollen tapestry is threaded with fine silk strands to portray "+
      vq_scene[SCENE_NUM]+". "+"An inscription is threaded along the "+
      "top of the tapestry.\n");
   add_item("inscription",
      "It is threaded along the top border of the tapestry. " +
      "Perhaps you can read it.\n");
   add_cmd_item("inscription","read","It reads: "+vq_prayer[SCENE_NUM]+".\n");
 
   add_item("doorway","It leads out of the chamber to the west.\n");
 
   add_exit(ROOM_DIR+"corr11", "west", 0);
   reset_room();
}
 
string exa_tray() {
   string desc="It is a silver serving tray";
   if (BachHere)
      if (OuzoHere)
         desc=desc+" with several pieces of bachlava and four ouzos "+
                   "sitting on top";
      else
         desc=desc+" with several pieces of bachlava sitting on top";
   else
      if (OuzoHere)
         desc=desc+" with four ouzos sitting on top";
 
   if ((BachHere||OuzoHere))
      desc=desc+", refreshments for an upcoming meeting.\n";
   else
      desc=desc+" with a few crumbs on it. Obviously you have missed "+
                "the party.\n";
 
   return desc;
}
string exa_bachlava() {
   if (BachHere)
      return
      "Bachlava is a sweet pastry made with fruit, "+
      "a favorite treat for the people of this area. No one is looking, "+
      "perhaps you could take it from the tray.\n";
   else
      return
      "There are only a few crumbs left on the tray, it is all gone.\n";
}
string exa_ouzo() {
   if (OuzoHere)
      return
      "Ouzo is a flavored alcoholic beverage, "+
      "a favorite drink for the people of this area. No one is looking, "+
      "perhaps you could take it from the tray.\n";
   else
      return "The ouzos on the tray are all taken now.\n";
}
 
int take(string ParmStr) {
   object TPlay=this_player();
   object TRoom=this_object();
   string *Parm;
   object bach;
   object ouzo;
   int    NumBachs=4;
   int    NumOuzos=4;
   int    FoundBach=0;
   int    FoundOuzo=0;
   int    i;
 
   if (!ParmStr) return 0;
   Parm=explode(ParmStr," ");
 
   for (i=0; i<sizeof(Parm); i++) {
      if ((Parm[i]=="bachlava")||(Parm[i]=="bachlavas")) FoundBach=1;
      if ((Parm[i]=="ouzo")||(Parm[i]=="ouzos")) FoundOuzo=1;
   }
 
   if ((FoundBach)&&(BachHere)) {
      write("You take the pieces of bachlava from the tray.\n");
      tell_room(TRoom,QCNAME(TPlay)+" takes the pieces of bachlava "+
                "from the tray.\n",TPlay);
      for (i=0; i<NumBachs; i++) {
         bach=clone_object(OBJ_DIR+"bachlava");
         bach->move(TPlay);
      }
      BachHere=0;
      return 1;
   }
 
   if ((FoundOuzo)&&(OuzoHere)) {
      write("You take the bottles of ouzo from the tray.\n");
      tell_room(TRoom,QCNAME(TPlay)+" takes the bottles of ouzo "+
                "from the tray.\n",TPlay);
      for (i=0; i<NumOuzos; i++) {
         ouzo=clone_object(OBJ_DIR+"ouzo");
         ouzo->move(TPlay);
      }
      OuzoHere=0;
      return 1;
   }
   return 0;
}
 
void init() {
   ::init();
   add_action("take","get");
   add_action("take","take");
}
