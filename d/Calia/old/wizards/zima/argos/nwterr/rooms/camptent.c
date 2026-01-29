/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object tcomm=0;
object dcomm=0;
int    there_are_full_bottles=1;
object bottle=0;
 
void make_tcomm() {
    if (tcomm) return;
    tcomm=clone_object(NPC_DIR+"tcommder");
    tcomm->equip_me();
    tcomm->move(THIS);
    tell_room(THIS, QCNAME(tcomm)+" salutes his superior.\n");
}
void make_dcomm() {
    if (dcomm) return;
    dcomm=clone_object(NPC_DIR+"dcommder");
    dcomm->equip_me();
    dcomm->move(THIS);
    tell_room(THIS, QCNAME(dcomm)+" rises from the chair.\n");
}
void reset_room() {
   make_tcomm();
   make_dcomm();
   there_are_full_bottles = 1;
}
 
void create_room() {
   set_short("Inside a tent");
   set_long(
       "You step inside a round canvas tent. A pole in the center " +
       "of the tent supports the top making it into the shape of " +
       "a cone. A small table and chair are the only furnishings in this " +
       "sparse shelter. The entrance to the tent is open to the east.\n");
 
   add_item("pole",
      "A tall wooden pole supporting the top of the tent.\n");
   add_item("top",
      "The pole supporting the top makes a cone above the circular tent.\n");
   add_item("chair",
      "It is a simple wooden chair. It doesn't look very comfortable.\n");
   add_item("entrance",
      "It is open to the east.\n");
   add_item("table",
      "It is a small wooden table, not what you would expect to be the " +
      "desk of a great leader, but it is sufficient for a camp. You " +
      "see a piece of parchment and some bottles on the table.\n");
 
   add_item("parchment",
      "It is a small piece of parchment with writing on it, "+
      "bearing a seal.\n");
   add_cmd_item("parchment","read",
      "It reads: Take command of the situation. The attacks on " +
      "foreigners must stop. Signed, Cosmopolitus of Argos.\n");
   add_item("writing",
      "It is barely legible on the parchment.\n");
   add_cmd_item("writing","read",
      "It reads: Take command of the situation. The attacks on " +
      "foreigners must stop. Signed, Cosmopolitus of Argos.\n");
   add_item("seal",
      "it is a circular layer of wax stamped on the piece of parchment " +
      "beneath the writing. It is imprinted with the image of a shield " +
      "emblazoned with a winged horse surmounted by a crown. Some " +
      "strange writing around the seal reads: Sphragis Archon " +
      "Cosmopolitus.\n");
 
   add_item("bottles","@@exa_bottles");
   add_cmd_item("bottles","take","@@take_bottles");
 
   /* exits */
   add_exit(ROOM_DIR+"camp","east",0);
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
