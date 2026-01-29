/*
**  Temple of Dephonia, Ground Level Stairway
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 2
object *guard=allocate(NUM);
 
make_monster(int i)
{
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"towguard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" walks up the steps.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
}
 
create_room() {
   set_short("Tower in the Temple of Dephonia");
   set_long(break_string(
      "Sunlight beams through a window of this diamond-shaped " +
      "tower which serves as a stairwell leading to the upper and " +
      "lower levels of the temple. The light casts a happy radiance " +
      "on a statue which sits atop a pedestal in the center of the " +
      "chamber. The steps along the southeastern wall lead up, " +
      "while those along the southwestern lead down, and there " +
      "is an entrance to the corridor to the north.\n",70));
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("corridor", break_string(
      "There is an entrance to it to the north",70));
 
   add_item(({"stairwell","steps","stairs"}), break_string(
      "Made of slick black marble, the wide steps with no bannisters " +
      "lead to the upper level along the southeastern wall and " +
      "to the lower level along the southwestern wall.\n",70));
 
   add_item("window",break_string(
      "The window is a simple rectangular hole in the southwestern " +
      "wall of the temple. Looking outside you see only the thick " +
      "forest of black pines which surround the temple.\n",70));
 
   add_item("statue", break_string(
      "It is a life-sized statue of a woman, wearing a long robe " +
      "which has a raven encircled by twelve stars on the breast, " +
      "and a golden medallion about her neck. " +
      "She grasps a scroll in her right hand and her left hand is " +
      "upraised. She has an aura of wisdom about her but also seems " +
      "to have a motherly gaze to her eyes.\n",70));
 
   add_item("pedestal",break_string(
      "The pedestal is a short diamond-shaped column of glassy black " +
      "marble upon which the statue stands. There is an inscription " +
      "written on one of the smooth faces.\n",70));
 
   add_item("inscription", break_string(
      "It is sculpted into the face of the pedestal. Perhaps you can " +
      "read it.\n",70));
 
   add_cmd_item("inscription","read",
      "DELPHIA - THE FIRST HIEROPHANT - SEER OF THE VISION.\n");
 
 
   add_exit(ROOM_DIR+"corr15",  "north", 0);
   add_exit(ROOM_DIR+"stair2",  "up", "@@check_pass");
   add_exit(ROOM_DIR+"stair0",  "down","@@notopen");
   reset_room();
}
 
int notopen() {
   write("The lower level is undergoing repairs and is too dangerous.\n");
   return 1;
}
 
int check_pass() {
   object pass=0;
   int    i;
   int    gn=-1;
 
   for (i=0; i<NUM; i++)
      if ((guard[i])&&(present(guard[i],this_object()))) gn=i;
 
   if (gn==-1) return 0; /* no guards here */
   pass = present(CAPTNSEAL,this_player());
   if (pass) {
      write("You show your small seal to the dephonian temple guard.\n");
      write("The dephonian temple guard allows you to pass.\n");
      return 0;
      }
   else {
      guard[gn]->command("emote pushes you back.");
      guard[gn]->command(
      "say you must have permission from the Captain to pass here.");
      return 1;
   }
}
