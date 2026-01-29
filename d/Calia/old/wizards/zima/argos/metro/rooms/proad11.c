/*
**   ARGOS - Metro - Protos and Chiphas
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
   set_short("Chiphas and Protos Roads");
   set_long(
       "You come to the intersection of Chiphas and Protos roads on "+
       "the city's western side. A set of steps lead up to the portico of "+
       "one of the city's temples to the west, where you see an enormous "+
       "statue staring out over the city. The buildings of the commercial "+
       "district line the eastern side of Protos road to the north and "+
       "south, while Chiphas leads east to the heart of the city.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Protos road runs north and south between a temple and a row "+
       "of commercial buildings, while Chiphas leads east.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the east side like white cubes.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. A set of steps lead up to its "+
       "portico.\n");
   add_item("portico",
       "It is a covered structure which extends from the face of "+
       "the temple, serving as an entrance to the shrine. It is "+
       "supported by a row of pillars along the front identical "+
       "to those which line the temple's walls.\n");
   add_item("statue",
       "It is an enormous statue standing on the floor of the temple's "+
       "portico. Perhaps you should walk up the steps to get a closer "+
       "view.\n");
   add_item("steps",
       "They lead up to the portico of the temple to the west.\n");
   add_item("pillars",
       "They support the portico of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"proad10", "north",0);
   add_exit(ROOM_DIR+"proad12","south",0);
   add_exit(ROOM_DIR+"croad8",  "east",0);
   add_exit(ARXTEMP_DIR+"rooms/port2","steps","@@steps");
   reset_room();
}
 

int steps() {
   write("You climb the steps of the temple up to the west.\n");
   return 0;
}
