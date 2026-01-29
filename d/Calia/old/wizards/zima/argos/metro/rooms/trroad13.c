/*
**   ARGOS - Metro - Tritos Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
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
    tell_room(THIS, QCTNAME(citizen[i])+" walks down the road.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
 
void create_room() {
   set_short("Tritos Road");
   set_long(
       "Song birds dance overhead in the gentle breeze, adding to "+
       "the tranquility of your stroll down the southern end of "+
       "Tritos road. The hedge of the park continues to run along "+
       "the west side of the road, while the curve of columns which "+
       "front the Amphitheatre comes near the road at its corner "+
       "to the east.\n");
 
   add_item("park",
       "It is surrounded with a well-trimmed hedge which walls the "+
       "road on the west side. You see no entrance to it here.\n");
   add_item("road","It runs north and south.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
   add_item(({"Amphitheatre","amphitheatre"}),
       "The Ampthitheatre of Argos sits on the eastern side of the "+
       "road, an open-air place where citizens "+
       "and visitors alike gather to see dramatic and comic productions. "+
       "It is faced with a line of very tall "+
       "columns which stand in a quarter-circle from its northeastern "+
       "to its southwestern corner. You see no entrance between the "+
       "massive columns here.\n");
   add_item(({"column","columns"}),
       "Standing in a curving line, the columns reach high into the "+
       "sky and form the facade of the Amphitheatre, curving from "+
       "its northeastern to its southwestern corners. Each column "+
       "is topped with a capitol sculpted with happy and sad-faced "+
       "actors' masks.\n");
   add_item("birds","They swoop overhead between the park and the "+
            "amphitheatre, their high-pitched song carried in the "+
            "breeze.\n");
 
 
   /* exits */
   add_exit(ROOM_DIR+"trroad12","north",0);
   add_exit(ROOM_DIR+"trroad14","south",0);
   reset_room();
}
