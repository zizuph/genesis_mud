/*
**   ARGOS - Metro - Alpharon road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   11/12/95   Zima       Created
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
    guard[i]=clone_object(NPC_DIR+"citizen");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" strolls up.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
void create_room() {
   set_short("Alpharon Road");
   set_long(
       "You are standing on Alpharon Road, where a set of steps leads "+
       "up to a small entrance in the great temple to the north. The "+
       "circular exterior of a columned structure to the south comes "+
       "near to the street here, where you can see the great craftsmanship "+
       "of its high columns. The road continues to the east and west "+
       "through this quiet southwestern part of the city.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west along the south side of town.\n");
   add_item(({"structure","circular structure"}),
       "It is an enormous circular building, which seems to have no "+
       "walls except two levels of columns which ring around it. "+
       "The building also seems to have no roof, so it is probably "+
       "some sort of outdoor theatre or arena.\n");
   add_item("columns",
       "They are closely set together in two levels of rings to form "+
       "the wall of the structure to the south.\n");
   add_item("temple",
      "It is a massive structure of white marble, its high walls buttressed "+
      "by tall pillars. A set of steps lead up to an entrance to the "+
      "temple.\n");
   add_item(({"steps","entrance"}),
      "A set of steep steps lead up into the temple, but the entranced "+
      "is closed.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
   reset_room();
 
   /* exits */
   add_exit(ROOM_DIR+"aroad2",   "west",0);
   add_exit(ROOM_DIR+"aroad4",   "east",0);
}
