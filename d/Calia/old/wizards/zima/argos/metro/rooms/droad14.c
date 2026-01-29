/*
**   ARGOS - Metro - Dueteros Road
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
object *citizen=allocate(NUM);
 
void make_monster(int i) {
    if (citizen[i]) return;
    citizen[i]=clone_object(NPC_DIR+"citizen");
    citizen[i]->equip_me();
    citizen[i]->move(THIS);
    tell_room(THIS, QCNAME(citizen[i])+" walks up.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
}
 
void create_room() {
   set_short("Deuteros Road");
   set_long(
       "A small songbird circles over the street here, darting in "+
       "and out of the hedge around the park to the east. The long "+
       "wall of one of the city's major buildings lines the road "+
       "to the west, blue tile trimming it near the top and bottom. "+
       "Deuteros road leads north and south through this tranquil "+
       "part of town.\n");
 
   add_item("park",
       "It is surrounded with a tall well-trimmed hedge to the east. "+
       "You don't see an entrance to it here.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park. It walls the road on the east side.\n");
   add_item("building",
       "It a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"road","roads","street","streets"}),
       "Deuteros road runs north and south between the building and "+
       "the park.\n");
 
   reset_room();
   /* exits */
   add_exit(ROOM_DIR+"droad13",  "north",0);
   add_exit(ROOM_DIR+"aroad10",  "south",0);
}
