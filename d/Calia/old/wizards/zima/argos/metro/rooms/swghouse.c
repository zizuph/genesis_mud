/*
**   ARGOS - Metro - Alpharon road (West End)
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   11/12/95   Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 2
object *guard=allocate(NUM);
object tcomm=0;
object bottle=0;
int    there_are_full_bottles=1;
 
void make_guard(int i) {
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"strguard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" salutes enters and salutes.\n");
}
 
void make_tcomm() {
    if (tcomm) return;
    tcomm=clone_object(NPC_DIR+"tcommder");
    tcomm->equip_me();
    tcomm->move(THIS);
    tell_room(THIS, QCNAME(tcomm)+" rises from the chair.\n");
}
 
void reset_room() {
   int i;
   make_tcomm();
   for (i=0; i<NUM; i++) make_guard(i);
   there_are_full_bottles = 1;
}
 
void create_room() {
   set_short("Inside a guardhouse");
   set_long(
       "A small table and chair are the only furnishings of this very "+
       "small shed, a blue banner hanging on the west wall its only "+
       "ornamentation. The plain marble walls rise up to a conic roof "+
       "which was made to look like that of a round tent.\n");
 
   add_item("banner",
      "It is a blue banner made of silk bearing the royal arms of Argos, "+
      "a shield emblazoned with a rampant winged horse surmounted by a "+
      "crown with three jewels.\n");
   add_item("chair",
      "It is a simple wooden chair. It doesn't look very comfortable.\n");
   add_item("entrance",
      "It is open to the north.\n");
   add_item("table",
      "It is a small wooden table, not what you would expect to be the " +
      "desk of a great leader, but it is sufficient for a guardhouse. You " +
      "see a piece of parchment and some bottles on the table.\n");
   add_item("parchment",
      "It is a small piece of parchment with writing on it, "+
      "bearing a seal.\n");
   add_cmd_item(({"writing","parchment"}),"read",
      "It reads: Keep the southwest bridge open as long as there "+
      "is no trouble. Signed, Cosmopolitus of Argos.\n");
   add_item("writing",
      "It is barely legible on the parchment.\n");
   add_item("seal",
      "it is a circular layer of wax stamped on the piece of parchment " +
      "beneath the writing. It is imprinted with the image of a shield " +
      "emblazoned with a winged horse surmounted by a crown. Some " +
      "strange writing around the seal reads: Sphragis Archon " +
      "Cosmopolitus.\n");
 
   add_item("bottles","@@exa_bottles");
   add_cmd_item("bottles","take","@@take_bottles");
 
   /* exits */
   add_exit(ROOM_DIR+"aroad1","north",0);
   reset_room();
}
 
string exa_bottles() {
   if (there_are_full_bottles) return
      "There are several bottles on the table. Some look full.\n";
   return
      "There are a couple of bottles on the table, but they are empty.\n";
}
 
int take_bottles() {
   int j;
 
   if (there_are_full_bottles) {
      for (j=0; j<3; j++) {
         bottle=clone_object(OBJ_DIR+"retsina");
         bottle->move(this_player());
         bottle=0;
      }
      write("You take three bottles from the table.\n");
      there_are_full_bottles = 0;
   }
   else write("The bottles are empty, so you just leave them.\n");
   return 1;
}
