/*
**   ARGOS - Metro - Dueteros road
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
 
#include "toequest.c"
 
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
   set_short("Chiphas and Deuteros Roads");
   set_long(
       "You come to the intersection of Chiphas and Deuteros roads "+
       "in the center of the city of Argos. The tall statue of one "+
       "of the past rulers of the civilization stands atop a high "+
       "pedestal in the center of the intersection. The commercial "+
       "district lies north of Chiphas road which runs east and "+
       "west, while the corner of one of the city's large buildings "+
       "sits to the southwest. There is an entrance to a park which "+
       "is surrounded by a well-trimmed hedge to the southeast. "+
       "Deuteros leads north into the commercial district and "+
       "south between the large building and the park.\n");
 
   add_item("statue",
       "It is the statue of a regal bearded man, wearing a short "+
       "tunic with an ornate strip down the front split, belted "+
       "with a thick thong. Surprisingly he holds a mallot in "+
       "his hand instead of a scepter. His eyes gaze out over "+
       "the commercial district to the north.\n");
   add_item("pedestal",
       "It is an ornately sculpted block of marble on top of "+
       "which the statue stands. An inscription is written "+
       "across the face of the pedestal.\n");
   add_item("inscription",
       "It is written on the pedestal. Perhaps you can read it.\n");
   add_cmd_item("inscription","read",
       "It reads: BASILEUS : FOURTH MONARCH OF ARGOS : 89-112 AT.\n");
   add_item(({"toe","toe of statue","toe on statue"}),
       "The toe of the king looks highly polished compared to "+
       "the rest of the statue.\n");
   add_item(({"road","roads","street","streets"}),
       "Deuteros road runs north and south while Chiphas leads east "+
       "and west.\n");
   add_item(({"shops","establishments","buildings","district",
       "commercial district"}),
       "They are one-level buildings constructed of marble, lining "+
       "the Chiphas on the north sides like white cubes.\n");
   add_item("building",
       "It a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item("park",
       "It is surrounded with a well-trimmed hedge. There is an "+
       "entrance to it to the southeast.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
 
   reset_room();
   /* exits */
   add_exit(ROOM_DIR+"droad10", "north",0);
   add_exit(ROOM_DIR+"droad12", "south",0);
   add_exit(ROOM_DIR+"croad11", "east",0);
   add_exit(ROOM_DIR+"croad9",  "west",0);
   add_exit(ROOM_DIR+"park1",   "southeast",0);
   toe_quest_set_statue_prop(TOE_QUEST_BASILEUS);
}
