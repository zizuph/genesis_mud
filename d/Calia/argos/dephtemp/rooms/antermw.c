/*
**  Temple of Dephonia - Western Anteroom of the Sanctum
**
** The Delta (4th)   tome of the Vision Quest is found on the pulpit
**     here.
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
#include "defs.h"
int tome_here=1; /* tome is present when loaded */
 
void return_object(int ObjNum) {
   tome_here=1;
}
 
create_room() {
   set_short("West Anteroom of the Temple of Dephonia");
   set_long(break_string(
      "Dozens of tall candles line the walls of this odd-shaped " +
      "chamber, filling it with their light and perfumed aroma. " +
      "This chamber is an auditorium, a single aisle leading west " +
      "to east through rows of benches, encirling a pulpit on the " +
      "eastern end. Two large pillars mark the arched doorway to the "+
      "west, the aisle leads behind the pulpit into another chamber " +
      "to the east.\n",70));
 
   add_item("candles", break_string(
      "Tall red candles sit in golden holders on the walls all around "+
      "the chamber. Their light and incense give a somber mood " +
      "to the room.\n",70));
 
   add_item(({"walls","chamber","auditorium"}), break_string(
      "The chamber is arrow-shaped with the northern and southern "+
      "walls angling to a point at the western arched entrance. " +
      "The east "+
      "wall of the chamber is round, making you think the chamber "+
      "to the east must be circular.\n",70));
 
   add_item("benches", break_string(
      "Long benches of polished mohagany run north-south, clipped "+
      "by the arrow-shaped walls, a single aisle cut through " +
      "the center.\n",70));
 
   add_item("aisle", break_string(
      "It runs east-west through the center of the chamber, ending "+
      "in a circular dais on the eastern end upon which stands "+
      "a pulpit.\n",70));
 
   add_item("dais",break_string(
      "It is a simple circular slab of marble which elevates the "+
      "pulpit above the floor of the auditorium.\n",70));
 
   add_item(({"tome","tome on pulpit","tome from pulpit",
              "tome from the pulpit"}), "@@exa_tome");
   add_cmd_item("tome from pulpit",({"take","get"}),"@@take_tome");
   add_cmd_item("tome","take","Take tome from what?\n");
   add_cmd_item("tome","get", "Get tome from what?\n");
   add_cmd_item(({"tome on pulpit","tome from pulpit","tome",
                  "tome from the pulpit"}),"read", "@@read_tome");
 
   add_item("pillars", break_string(
      "Two massive columns of marble which buttress the arched " +
      "entrance to the anteroom to the west.\n",70));
 
   add_item(({"doorway","entrance","arch"}), break_string(
      "A large arch supported by two pillars makes for a "+
      "wide entrance to the anteroom from the west.\n",70));
 
   add_item("pulpit", "@@exa_pulpit");
 
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"corr13","west",0);
   add_exit(ROOM_DIR+"sanct","east",0);
}
 
string
exa_pulpit() {
   if (tome_here) {
       return break_string(
       "It is a large, piously decorated podium behind which "+
       "a priestess leads the worship and instruction of the "  +
       "members of the Order. You see an ancient tome laying "  +
       "on top.\n",70);
       }
    else
       return break_string(
       "It is a large, piously decorated podium behind which "+
       "a priestess leads the worship and instruction of the "  +
       "members of the Order.\n",70);
}
 
string
exa_tome() {
   if (tome_here)
       return "It is laying on top of the pulpit in plain view.\n";
    else
       return "You find no tome here.\n";
}
 
string
read_tome() {
   if (tome_here)
       return "You must take it from the pulpit to read it.\n";
    else
       return "You find no tome here.\n";
}
 
int
take_tome() {
   object tome=0;
   object Thisroom=0;
   if (tome_here) {
      tome=clone_object(OBJ_DIR+"tomed"); /* Delta tome */
      Thisroom=environment(this_player());
      tome->move(this_player());
      write("You take the tome from the pulpit.\n");
      tell_room(Thisroom, QCNAME(this_player())+
                " takes the tome from the pulpit.\n",this_player());
      tome_here=0; /* tome gone now */
      }
   else
      write("You find no tome here.\n");
   return 1;
}
