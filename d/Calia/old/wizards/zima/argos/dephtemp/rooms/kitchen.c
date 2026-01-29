/*
**  Temple of Dephonia, Kitchen
**
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
 
object youngservant=0;
object oldservant=0;
 
void
reset_room()
{
    if (!oldservant) {
       oldservant=clone_object(NPC_DIR+"oldserv");
      oldservant->equip_me();
       oldservant->move(THIS);
       tell_room(THIS, QCNAME(oldservant)+" walks in from the corridor.\n");
    }
    if (!youngservant) {
       youngservant=clone_object(NPC_DIR+"yungserv");
       youngservant->equip_me();
       youngservant->move(THIS);
       tell_room(THIS, QCNAME(youngservant)+" walks in from the corridor.\n");
    }
}
 
create_room() {
   set_short("Kitchen in the Temple of Dephonia");
   set_long(
      "The delicious smell of food cooking in the large hearth which "+
      "takes up the western wall makes you think of home. This chamber "+
      "is where the food for the Order is prepared by the servants " +
      "of the temple. A large tub sits along the eastern wall next "+
      "to a long table. There is an entrance to the corridor to "+
      "the east, and a doorway to a back room to the north.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("food","It is cooking in the pots in the hearth.\n");
   add_item(({"pot","pots"}), "They hang above the fires of the hearth, "+
              "the wholesome smell of food steaming from them.\n");
   add_item(({"fire","fires"}), "There are four fires burning in "+
              "the long hearth, heating the food in the pots.\n");
   add_item("hearth","Made of large stones, the hearth runs the "+
            "entire length of the west wall. Four fires burn inside "+
            "of it, heating pots of food suspended above.\n");
   add_item("tub","It is a long iron tub filled with hot water, "+
            "used to wash the utensils and dishes.\n");
   add_item(({"utensils","dishes"}), "Piles of dirty dishes and "+
              "eating utensils sit on top of the table.\n");
   add_cmd_item(({"utensils","dishes","utensils on table",
                  "dishes on table","dishes from table",
                  "utensils from table"}),({"take","get"}),
                  "Who would want a bunch of dirty dishes?\n");
   add_cmd_item(({"utensils","dishes","utensils on table",
                  "dishes on table","dishes from table",
                  "utensils from table"}),"wash",
                  "No, you might break something.\n");
   add_item("table","It is a long wooden table of no decor, covered "+
            "in dishes and utensils waiting to be washed.\n");
   add_item("goblet","You find no goblet.\n");
   add_cmd_item("goblet","wash","@@wash_goblet");
   add_item("bowl","You find no bowl.\n");
   add_cmd_item("bowl","wash","@@wash_bowl");
 
   add_exit(ROOM_DIR+"corr21","east",0);
   add_exit(ROOM_DIR+"winery","north",0);
   reset_room();
}
 
void wash_dirty(string short, string obj_id) {
   object TPlay=this_player();
   object TRoom=environment(TPlay);
   object obj=present(obj_id,TPlay);
   if (obj)
      if (obj->query_prop(IS_DIRTY)) {
         /* object is worth 5 times as much clean as dirty */
         obj->add_prop(IS_DIRTY,0);
         obj->add_prop(OBJ_I_VALUE,((obj->query_prop(OBJ_I_VALUE))*5));
         write("You wash the "+short+" in the hot water of the tub.\n");
         tell_room(QCNAME(TPlay)+" washes a "+short+" in the tub.\n",TPlay);
         }
      else
         write("The "+short+" is already clean!\n");
   else
      write("You have no "+short+" to wash.\n");
}
 
int wash_bowl()   { wash_dirty("bowl",DIRTY_BOWL);     return 1; }
int wash_goblet() { wash_dirty("goblet",DIRTY_GOBLET); return 1; }
