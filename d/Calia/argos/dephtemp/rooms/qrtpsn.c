/*
**  Temple of Dephonia, Priestess' Quarters
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
 
#define NUM 4
object *priestess=allocate(NUM);
int    tome_here=1;
 
void return_object(int ObjNum) {
   tome_here=1;
}
 
void
make_monster(int i)
{
    if (priestess[i]) return;
    priestess[i]=clone_object(NPC_DIR+"qrtprsts");
    priestess[i]->equip_me();
    priestess[i]->move(THIS);
    tell_room(THIS, QCNAME(priestess[i])+" walks in from the corridor.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
create_room() {
   set_short("Priestess Quarters in the Temple of Dephonia");
   set_long(
      "This odd-shaped room is one of the chambers for the priestesses "+
      "of the Order. Beds line the west, northeast and east walls "+
      "set in perfect order, while two large wardrobes sit on "+
      "either side of the doorway to the south. A small desk sits "+
      "at the foot of one of the beds. You look up and notice a mosaic "+
      "set in the plaster of the ceiling.\n");
 
   add_item(({"mosaic","ceiling"}),
              "Made of shards of colored glass, the mosaic is pieced "+
              "together in the image of a serpent twisted around a "+
              "wreath of hemlock.\n");
 
   add_item(({"room","chamber","walls"}), "The chamber is constructed "+
              "with four walls, one to the east, west and south, "+
              "while the northern wall slants from the southeast "+
              "to the northwest.\n");
 
   add_item(({"doorway","corridor"}), "It is to the south.\n");
 
   add_item(({"bed","beds"}), "They are simple single beds made of "+
              "dark pine wood. They are set in perfect order around "+
              "the perimeter of the room, their heads to the walls.\n");
 
   add_item("desk","@@exa_desk");
 
   add_item(({"tome","tome on desk","tome from desk",
           "tome from the desk"}), "@@exa_tome");
   add_cmd_item("tome from desk",({"take","get"}),"@@take_tome");
   add_cmd_item("tome","take","Take tome from what?\n");
   add_cmd_item("tome","get", "Get tome from what?\n");
   add_cmd_item(({"tome on desk","tome from desk","tome",
            "tome from the desk"}),"read", "@@read_tome");
 
 
   add_item(({"wardrobe","wardrobes"}), "The wardrobes are tall "+
              "cabinet-like furnishings, one each on either side "+
              "of the doorway to the south. You guess they contain "+
              "the clothes and other items of the priestesses who sleep "+
              "here.\n");
   add_cmd_item(({"wardrobe","wardrobes"}), ({"open","unlock"}),
              "The wardrobes are locked and can not be opened.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"corr28","south",0);
   reset_room();
}
 
string exa_desk() {
   string desc="It is a small desk of dark pine used for reading and "+
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
      tome=clone_object(OBJ_DIR+"tomez"); /* Zeta tome */
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
