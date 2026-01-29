/*
**   ARGOS - Metro - Alpharon and Protos roads
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**  11/15/95    Zima       Western part of road opened (conn to aroad6)
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
   set_short("Alpharon and Protos Roads");
   set_long(
       "You come to the intersection of Alpharon and Protos roads on "+
       "the southwestern side of town. The roads cross between three "+
       "of the city's large structures, a temple to the northwest and a "+
       "public building with an angled roof to the northeast. You see "+
       "an unusual circular structure with walls of closely set columns "+
       "to the southwest, while a pleasant grove of cherry trees grows "+
       "to the southeast. A path leads to the courtyard "+
       "of the circular structure, while Protos road continues north "+
       "and south, and Alpharon road leads east and west.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west while Protos leads north and "+
       "south.\n");
   add_item(({"structure","circular structure"}),
       "It is an enormous circular building, which seems to have no "+
       "walls except two levels of columns which ring around it. "+
       "The building also seems to have no roof, so it is probably "+
       "some sort of outdoor theatre or arena. There is a path "+
       "leading to its courtyard to the southwest.\n");
   add_item("columns",
       "They are closely set together in two levels of rings to form "+
       "the wall of the structure to the southwest.\n");
   add_item("courtyard",
       "It is the courtyard of the circular building. There is a path "+
       "leading to it to the southwest. Perhaps you could take a closer "+
       "look.\n");
   add_item("temple",
      "You see the corner of one of the city's temples to the northwest, "+
      "its high walls buttressed by tall pillars. You see no entrance to "+
      "the temple here.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
   add_item(({"building","public building"}),
       "It is a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"grove","trees","cherry trees","cherry grove"}),
       "A grove of cherry trees grows in the souteastern corner of "+
       "the intersection, perfuming the roads with their sweet scent.\n");
 
   reset_room();
 
   /* exits */
   add_exit(ROOM_DIR+"proad14",  "north",0);
   add_exit(ROOM_DIR+"proad16",  "south","@@closed");
   add_exit(ROOM_DIR+"aroad6",   "west",0);
   add_exit(ROOM_DIR+"aroad8",   "east",0);
   add_exit(ARENA_DIR+"rooms/court","southwest",0);
}
 
int closed() {
   write("There seems to be nothing of interest down there, so you "+
         "decide not to go that way.\n");
   return 1;
}
