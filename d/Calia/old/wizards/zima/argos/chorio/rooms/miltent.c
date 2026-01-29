/* HQ of the village militia
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/30/97     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  NUM 3
 
object *guard=allocate(NUM);
 
void make_guard(int i) {
   if (guard[i]) return;
   if (i==0)
      guard[i]=clone_object(NPC_DIR+"captain");
   else
      guard[i]=clone_object(NPC_DIR+"guard");
   guard[i]->equip_me();
   guard[i]->move(THIS);
   tell_room(THIS,QCNAME(guard[i])+" steps into the tent.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_guard(i);
}
 
void create_room() {
   set_short("Inside a tent");
   set_long(
       "You step inside a round canvas tent, the headquarters of the "+
       "local militia forces which protect the village. A pole in the "+
       "center of the tent supports the top making it into the shape of " +
       "a cone. A small table and chair are the only furnishings in this " +
       "sparse shelter. The entrance to the tent is open to the west.\n");
 
   add_item("pole",
      "A tall wooden pole supporting the top of the tent.\n");
   add_item("top",
      "The pole supporting the top makes a cone above the circular tent.\n");
   add_item("chair",
      "It is a simple wooden chair. It doesn't look very comfortable.\n");
   add_item("entrance",
      "It is open to the west.\n");
   add_item("table",
      "It is a small wooden table, not what you would expect to be the " +
      "desk of a great leader, but it is sufficient for a camp. You " +
      "see a piece of parchment sitting on it.\n");
   add_item("parchment",
      "It is a small piece of parchment with writing on it, "+
      "bearing a seal.\n");
   add_cmd_item(({"parchment","writing"}),"read",
      "It reads: I offer you and your people any assistance needed in "+
      "defense of Chorio Hagios. Just ask for it and it shall be yours. "+
      "Signed, Cosmopolitus King of Argos.\n");
   add_item("writing",
      "It is barely legible on the parchment.\n");
   add_item("seal",
      "it is a circular layer of wax stamped on the piece of parchment " +
      "beneath the writing. It is imprinted with the image of a shield " +
      "emblazoned with a winged horse surmounted by a crown. Some " +
      "strange writing around the seal reads: Sphragis Archon " +
      "Cosmopolitus.\n");
 
   /* exits */
   add_exit("street01","west",0);
   reset_room();
}
