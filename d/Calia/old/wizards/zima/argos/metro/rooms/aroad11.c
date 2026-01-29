/*
**   ARGOS - Metro - Alpharon Road, at the path to the Palace
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 4
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
   set_short("Alpharon Road");
   set_long(
       "You are on Alpharon road on the south side of town, where a tall "+
       "hedge walls the road with evergreen on the north side. A small "+
       "path paved with royal-blue tile leads off the road to the south "+
       "through a perfumed grove of flowering cherry trees.\n");
 
   add_item("path",
       "It is paved with square tiles, a dark royal-blue in color, each "+
       "fired with a gold border.\n");
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west between the tall hedge and the "+
       "grove of cherry trees.\n");
   add_item(({"grove","trees","cherry trees","cherry grove"}),
       "A grove of cherry trees grows along the southern side of "+
       "the street, perfuming the road with their sweet scent.\n");
   add_item("park",
       "It lies to the north and is surrounded by a well-trimmed hedge "+
       "of evergreen.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"aroad10", "west",0);
   add_exit(ROOM_DIR+"aroad12", "east",0);
   add_exit(PALACE_DIR+"rooms/court2","south",0);
   reset_room();
}
