/*
**   ARGOS - Metro - Lambdos road
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
   set_short("Lambdos Road");
   set_long(
       "A grove of oak trees to the north shades this stretch of Lambdos "+
       "road as you walk along the northern side of town. A row of "+
       "marble buildings line the south side of the road, stretching "+
       "further east. The establishment to the south seems to be "+
       "newly renovated, a bright blue flag hanging next to the "+
       "entrance.\n");
 
   add_item(({"buildings","establishments","shops"}),
       "They are a row of one-level marble buildings which house "+
       "the local businesses and other public establishments.\n");
   add_item("flag",
       "It is hanging from a pole which angles from its base on "+
       "the wall of the building to the south. It is made of blue "+
       "silk and bears the royal arms, a shield emblazoned with a "+
       "winged horse surmounted by a crown with three jewels.\n");
   add_item(({"road","roads","street","streets"}),
       "It is an old road made of white marble slabs. It runs east "+
       "and west along the northern side of town.\n");
   add_item(({"building","establishment"}),
       "It is a one-level building made of marble, its outer walls "+
       "glisten in the sunlight making it look newly renovated.\n");
   add_item(({"woods","trees","area","grove","oaks","oak trees"}),
       "A small grove of oak trees shade the road on the north "+
       "side.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"lroad7",  "west",0);
   add_exit(ROOM_DIR+"lroad9",  "east",0);
   add_exit(ROOM_DIR+"visitctr","south",0);
}
