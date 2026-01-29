/*
**   ARGOS - Metro - Lambdos and Tetartos roads
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
   set_short("Lambdos and Tetartos Roads");
   set_long(
       "You come to the northeastern corner of the central district of "+
       "the city of Argos at the intersection of Lambdos and Tetartos "+
       "roads. Shops and other local establishments line the streets to "+
       "the south and west, while Tetartos the roads lead into wooded "+
       "areas to the north and east.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Lambdos road runs east and west while Tetartos leads north and "+
       "south.\n");
   add_item(({"shops","establishments"}),
       "They are one-level buildings constructed of marble, lining "+
       "the streets to the west and south like white cubes.\n");
   add_item(({"woods","trees","areas","wooded areas"}),
       "The roads lead north and east through wooded areas which "+
       "look pretty abandoned and uninteresting.\n");
 
   reset_room();
   /* exits */
   add_exit(ROOM_DIR+"proad6","north","@@closed");
   add_exit(ROOM_DIR+"troad8","south",0);
   add_exit(ROOM_DIR+"lroad15","west",0);
   add_exit(ROOM_DIR+"lroad17","east","@@closed");
}
 
int closed() {
   write("There seems to be nothing of interest down that road, "+
         "so you decide not to go that way.\n");
   return 1;
}
