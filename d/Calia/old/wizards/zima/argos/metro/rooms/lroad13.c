/*
**   ARGOS - Metro - Lambdos and Tritos Roads
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**   3/3/95     Zima       Citizens changed to street guard
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
    citizen[i]=clone_object(NPC_DIR+"strguard");
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
   set_short("Lambdos and Tritos Roads");
   set_long(
       "You come to the intersection of Lambdos and Tritos roads "+
       "on the north side of town. A set of steps lead up to the "+
       "portico of a large temple to the north, while the roads "+
       "lead through the cubic marble buildings of the commercial "+
       "district.\n");
   add_item(({"road","roads","street","streets"}),
       "Lambdos road runs east and west between a temple and a row "+
       "of commercial buildings, while Tritos leads south to the "+
       "heart of the city.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the south side like white cubes.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. A set of steps lead up to the "+
       "temple's portico from here.\n");
   add_item("portico",
       "It is a covered structure which extends from the face of "+
       "the temple, serving as an entrance to the shrine. It is "+
       "supported by a row of pillars along the front identical "+
       "to those which line the temple's walls.\n");
   add_item("pillars",
       "They support the roof of the portico, topped with capitols "+
       "sculpted with a ring of perched owls around the top.\n");
   add_item("steps",
       "They lead up to the temple's portico.\n");
   reset_room();
 
   /* exits */
   add_exit(THEMTEMP_DIR+"rooms/port3","steps","@@steps");
   add_exit(ROOM_DIR+"trroad8","south",0);
   add_exit(ROOM_DIR+"lroad12","west",0);
   add_exit(ROOM_DIR+"lroad14", "east",0);
   set_alarm(1.0,0.0,"reset_room");
}

int steps() {
   write("You climb the steps of the temple up to the north.\n");
   return 0;
}
