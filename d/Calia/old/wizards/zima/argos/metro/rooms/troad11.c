/*
**   ARGOS - Metro - Tetaros and Chiphas
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/14/95    Zima       Created
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
   for (i=0; i<NUM; i++) make_monster(i);
}
 
void create_room() {
   set_short("Tetartos and Chiphas Roads");
   set_long(
       "You come to the intersection of Chiphas and Tetartos roads on "+
       "the city's eastern side. A set of steps lead up to the portico of "+
       "one of the grand temples to the east, where you see a towering "+
       "statue gazing out over the city. The buildings of the commercial "+
       "district line the western side of Tetartos road to the north, while "+
       "the corner of the Amphitheatre sits on the south. Tetartos "+
       "leads north and south along the eastern side of the city, while "+
       "Chiphas runs west into the center of town.\n");
 
   add_item(({"amphitheatre","Amphitheatre"}),
       "It is an outdoor area where dramatic and comic presentations "+
       "are performed. It framed by a row of high columns. You don't see "+
       "an entrance into the amphitheatre through the columns here.\n");
   add_item("columns",
       "The columns rise high into the air, their capitols sculpted "+
       "with the images of actor's masks. They stand independently "+
       "around the Amphitheatre, paralleling the road to the south.\n");
   add_item(({"road","roads","street","streets"}),
       "Terartos road runs north and south while Chiphas leads west.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the west side to the north like white cubes.\n");
   add_item("statue",
       "It is a towering statue of a figure which gazes out over the "+
       "city. You could get a better look up on the portico.\n");
   add_item("temple",
       "It is one of the grand temples of the city, its walls rising "+
       "high above you. A line of massive pillars "+
       "support the portico which shades the temple's entrance, while "+
       "a set of steep steps leads up to the portico itself. The eyes "+
       "of a towering statue gaze out over the city from the center "+
       "of the portico.\n");
   add_item("pillars",
       "Massive pillars line the front of the temple, supporting the "+
       "roof of the portico. Each has an elaborate capitol sculpted "+
       "with doves in flight.\n");
   add_item("portico",
       "The portico is the covering over the entrance of the temple. "+
       "It is supported along its edge by a row of pillars, while set of "+
       "steps lead up onto its floor.\n");
   add_item("steps",
       "They lead up to the portico of the temple to the east.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"troad10","north",0);
   add_exit(ROOM_DIR+"troad12","south",0);
   add_exit(ROOM_DIR+"croad15","west",0);
   add_exit(PHARTEMP_DIR+"rooms/port2","steps","@@steps");
   reset_room();
}
 
int steps() {
   write("You climb the steps of the temple up to the east.\n");
   return 0;
}
