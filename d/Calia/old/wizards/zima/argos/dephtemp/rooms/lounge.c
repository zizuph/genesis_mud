/*
**  Temple of Dephonia, Commons/Lounge
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
#include "vqscenes.h"
int tome_here=1;
 
#define SCENE_NUM 5
#define NUM 2
object *priestess=allocate(NUM);
 
void return_object(int ObjNum) {
   tome_here=1;
}
 
void
make_monster(int i)
{
    if (priestess[i]) return;
    priestess[i]=clone_object(NPC_DIR+"elderpr");
    priestess[i]->equip_me();
    priestess[i]->move(THIS);
    tell_room(THIS, QCNAME(priestess[i])+" walks up to the table.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
create_room() {
   set_short("Commons of the Temple of Dephonia");
   set_long(
      "This large triangular chamber is the commons area for the "+
      "priests and priestesses who live in the temple. Couches are "+
      "arranged in squares in the three corners of the room, and there "+
      "is an interesting triangular table in the center of the room. "+
      "You admire a scene which has been sculpted into the marble of "+
      "the northwestern wall. A desk sits next to the doorway to the "+
      "corridor to the south.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item(({"couch","couches"}),
      "They are long benches of marble with no backs, cushioned with "+
      "red silk pillows. The ends of the benches are sculpted into "+
      "curls like the capital of a pillar. You imagine there has "+
       "been a lot of informal discussion in this room recently.\n");
   add_item("table",
      "It is a triangular column of marble sitting in the center of "+
      "the chamber. What looks like a strange game board has been "+
      "sculpted on top.\n");
   add_item(({"board","game board","game"}),
      "The triangular top of the table is divided by sculpted lines "+
      "into diamond-shaped spots. Small game pieces are positioned "+
      "in some of the diamonds.\n");
   add_item(({"pieces","game pieces"}),
      "They are tiny sculptures of warriors, kings and priests. "+
      "They look somewhat familiar, but you have never seen anything "+
      "exactly like these before.\n");
   add_item(({"sculpture","scene"}),
      "Figures and objects have been sculpted into the "+
      "marble of the northwestern wall to portray a scene of "+
       vq_scene[SCENE_NUM]+". A large rectangular frame surrounds "+
      "the sculpture.\n");
   add_item("frame",
      "It is a rectangular marble frame around the sculputure on the "+
      "wall. There is an inscription written along the lower part.\n");
   add_item("inscription",
      "It is written along the lower part of the frame. Perhaps you "+
      "can read it.\n");
   add_cmd_item("inscription","read",
      "It reads: "+vq_prayer[SCENE_NUM]+".\n");
 
   add_item("desk","@@exa_desk");
   add_item(({"tome","tome on desk","tome from desk",
           "tome from the desk"}), "@@exa_tome");
   add_cmd_item("tome from desk",({"take","get"}),"@@take_tome");
   add_cmd_item("tome","take","Take tome from what?\n");
   add_cmd_item("tome","get", "Get tome from what?\n");
   add_cmd_item(({"tome on desk","tome from desk","tome",
            "tome from the desk"}),"read", "@@read_tome");
 
   add_exit(ROOM_DIR+"corr27","south", 0);
   reset_room();
}
 
string exa_desk() {
   string desc="It is a large desk of polished oak for reading and "+
               "studying. ";
   if (tome_here)
      desc=desc+"You see an ancient tome laying on top of it.\n";
   else
      desc=desc+"\n";
   return desc;
}
 
string exa_tome() {
   if (tome_here)
      return "It is laying on top of the desk in plain view.\n";
   else
      return "You find no tome.\n";
}
 
string read_tome() {
   if (tome_here)
      return "You must take the tome from the desk to read it.\n";
   else
      return "You find no tome.\n";
}
 
 
int
take_tome() {
   object tome=0;
   object Thisroom=0;
   if (tome_here) {
      tome=clone_object(OBJ_DIR+"tomee"); /* Epsilon tome */
      Thisroom=environment(this_player());
      tome->move(this_player());
      write("You take the tome from the desk.\n");
      tell_room(Thisroom, QCNAME(this_player())+
                " takes the tome from the desk.\n",this_player());
      tome_here=0; /* tome gone now */
      }
   else
      write("You find no tome.\n");
   return 1;
}
