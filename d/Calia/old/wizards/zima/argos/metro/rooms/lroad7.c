/*
**   ARGOS - Metro - Lambdos and Protos roads
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
   set_short("Lambdos and Protos Roads");
   set_long(
       "You come to the northwestern corner of the central district of "+
       "the city of Argos at the intersection of Lambdos and Protos "+
       "roads. Shops and other local establishments line the streets to "+
       "the south and east, while Protos leads north into a wooded area and "+
       "Lambdos west toward the city gates.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Lambdos road runs east and west while Protos leads north and "+
       "south.\n");
   add_item(({"shops","establishments"}),
       "They are one-level buildings constructed of marble, lining "+
       "the streets to the east and south like white cubes.\n");
   add_item(({"woods","trees","area","wooded area"}),
       "Protos road runs north through a wooded area. It looks "+
       "pretty isolated and uninteresting.\n");
 
   reset_room();

   /* exits */
   add_exit(ROOM_DIR+"proad6","north","@@closed");
   add_exit(ROOM_DIR+"proad8","south",0);
   add_exit(ROOM_DIR+"lroad6","west",0);
   add_exit(ROOM_DIR+"lroad8","east",0);
}
 
int closed() {
   write("There seems to be nothing of interest to the north, so you "+
         "decide not to go that way.\n");
   return 1;
}
