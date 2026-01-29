/*
**  Temple of Dephonia, Second Level Stairway
**
** Player can get raven eggs from nest through window here, but
** there is nothing special about these eggs...at least not yet.
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/10/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 2
 
int    eggs_here=1;
object *guard=allocate(NUM);
 
make_monster(int i)
{
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"towguard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" walks up the steps.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
   eggs_here=1;
}
 
create_room() {
   set_short("Corridor in the Temple of Dephonia");
   set_long(
      "You are in a tower on the southern end of the temple of " +
      "Dephonia which serves as a stairwell between the levels. "+
      "The statue of a warrior sits on a pedestal in the middle "+
      "of the room, like an eternal guardian of the upper floors. "+
      "A set of steps leads down along the southeastern wall of "+
      "beneath a window, while another on the southwestern "+
      "leads up. There is an entrance to a corridor to the north.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("corridor", break_string(
      "There is an entrance to it to the north",70));
 
   add_item(({"out window","window"}),"It is a rectangular window "+
            "above the steps on the southeastern wall. You wonder what "+
            "you would see if you would look out the window.\n");
   add_cmd_item("out window","look","You look out the window "+
              "into the canopy of the mohagany and dark pine trees "+
              "which surround the temple. The branch of a nearby "+
              "tree almost sticks through the window.\n");
 
   add_item("branch","It is the branch of a nearby mahogany tree. "+
            "You see a bird's nest made on it.\n");
   add_item("nest","@@exa_nest");
   add_item(({"egg","eggs"}), "@@exa_eggs");
   add_cmd_item(({"eggs","eggs from nest"}), "take","@@take_eggs");
 
   add_item(({"stairwell","steps","stairs"}), break_string(
      "Made of slick black marble, the wide steps with no bannisters " +
      "lead to an upper level along the southwestern wall and " +
      "to a lower level along the southeastern wall.\n",70));
 
   add_item("statue",
            "It is a life-size bronze statue of a warrior arrayed in "+
            "elaborate "+
            "battle gear, including a helmet which covers his face "+
            "giving his head the appearance of a fierce bird. He "+
            "holds a large battleaxe in one hand and a shield "+
            "cast with a bull's head in the other.\n");
 
   add_item("pedestal",break_string(
      "The pedestal is a short diamond-shaped column of glassy black " +
      "marble upon which the statue stands. There is an inscription " +
      "written on one of the smooth faces.\n",70));
 
   add_item("inscription", break_string(
      "It is sculpted into the face of the pedestal. Perhaps you can " +
      "read it.\n",70));
 
   add_cmd_item("inscription","read",
      "DEMONSTRATES - WARRIOR OF DEPHONIA - MASTER OF THE GUARDIAN.\n");
 
 
   add_exit(ROOM_DIR+"corr21",  "north", "@@check_pass");
   add_exit(ROOM_DIR+"stair3",  "up", "@@check_pass");
   add_exit(ROOM_DIR+"stair1",  "down", 0);
   reset_room();
}
 
int check_pass() {
   object pass=0;
   int    i;
   int    gn=-1;
 
   for (i=0; i<NUM; i++)
      if (guard[i]) gn=i;
 
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
 
string exa_eggs() {
   if (eggs_here) return "You see two eggs nestled in the nest.\n";
   else           return "You find no eggs here.\n";
}
string exa_nest() {
   string desc="It is a small nest made by a bird on the branch of "+
               "a nearby tree. ";
   if (eggs_here) desc=desc+"You see two small eggs nestled inside.\n";
   else           desc=desc+"\n";
   return desc;
}
int take_eggs() {
   object TPlay=this_player();
   object TRoom=environment(TPlay);
   object raven=0;
 
   if (eggs_here) {
      (clone_object(OBJ_DIR+"ravenegg"))->move(TPlay);
      (clone_object(OBJ_DIR+"ravenegg"))->move(TPlay);
      write("You reach through the window and take two small "+
            "eggs from the nest.\n");
      tell_room(TRoom,QCNAME(TPlay)+" reaches through the window and gets "+
                "something.\n",TPlay);
      eggs_here=0;
      /* write but then the mother shows up and autoattacks! */
      raven=clone_object(NPC_DIR+"atkraven");
      tell_room(TRoom,QCNAME(raven)+" flies in through the window!\n");
      raven->move(TRoom);
      }
   else
      write("You find no eggs here.\n");
   return 1;
}
