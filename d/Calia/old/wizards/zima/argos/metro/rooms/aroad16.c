/*
**   ARGOS - Metro - Alpharon and Tetartos roads
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 2
object *guard=allocate(NUM);
 
void make_monster(int i) {
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"strguard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" takes his post.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
}
 
void create_room() {
   set_short("Alpharon and Tetartos Roads");
   set_long(
       "You come to the intersection of Alpharon and Tetartos roads on "+
       "the southeastern side of town. A long flat-topped building sits "+
       "in the northwestern corner, while a grove of cherry trees lines "+
       "Alpharon road to the west along its southern side. Maples and oaks "+
       "shade the eastern side of Tetartos road heading north and south.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west while Tetartos leads north and "+
       "south.\n");
   add_item(({"grove","trees","cherry trees","cherry grove"}),
       "A grove of cherry trees grows in the soutwestern corner of "+
       "the intersection, perfuming the roads with their sweet scent.\n");
   add_item("building",
       "It is a long, flat-topped building which stretches to the "+
       "west along the road. You can't make out what might be inside, "+
       "and you don't see an entrance to it here.\n");
   add_item(({"maples","oaks"}),
       "They shade Tetartos road on its east side, while Alpharon road "+
       "runs through the wooded area further east.\n");
 
   reset_room();
 
   /* exits */
   add_exit(ROOM_DIR+"troad14",  "north",0);
   add_exit(ROOM_DIR+"troad16",  "south","@@closed");
   add_exit(ROOM_DIR+"aroad15",  "west",0);
   add_exit(ROOM_DIR+"aroad17",  "east","@@closed");
}
 
int closed() {
   write("There seems to be nothing of interest down there, so you "+
         "decide not to go that way.\n");
   return 1;
}
