/*
**   ARGOS - Metro - Lambdos and Deuteros Roads
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
** 3/3/95        Zima       Citizens changed to street guards
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
    tell_room(THIS, QCNAME(citizen[i])+" takes his post.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
}
 
void create_room() {
   set_short("Lambdos and Deuteros Roads");
   set_long(
       "You come to the intersection of Lambdos and Deuteros roads "+
       "on the north side of Argos. One of the city's temples walls "+
       "the street to the north, while the buildings of the commercial "+
       "district line the roads to the south.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Lambdos road runs east and west between a temple and a row "+
       "of commercial buildings, while Deuteros heads south to the "+
       "heart of the city.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the south side like white cubes.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. You see some steps leading up "+
       "to the temple further east.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "sculpted with a ring of perched owls at the top.\n");
   add_item("steps",
       "They seem to lead up into the temple further east.");
   reset_room();
 
   /* exits */
   add_exit(ROOM_DIR+"droad8", "south",0);
   add_exit(ROOM_DIR+"lroad9","west",0);
   add_exit(ROOM_DIR+"lroad11","east",0);
}
