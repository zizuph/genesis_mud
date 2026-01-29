/*
**   ARGOS - Metro - Dueteros road
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
object *citizen=allocate(NUM);
 
void make_monster(int i) {
    if (citizen[i]) return;
    citizen[i]=clone_object(NPC_DIR+"citizen");
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
   set_short("Deuteros Road");
   set_long(
       "You are walking down Deuteros road in the heart of the city's "+
       "busy commercial district, the shops and other establishments "+
       "lining both sides of the road to the north and south. A sign "+
       "hangs over the entrance to the shop to the west, while a fresco "+
       "has been painted on the wall to the east.\n");
   add_cmd_item("sign","read","It reads: KATASEMAS EMPORIUM.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Deuteros road runs north and south between the shops and other "+
       "businesses.\n");
   add_item(({"shops","establishments","buildings","enterprises"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the both sides like white cubes.\n");
   add_item("sign",
       "It is a marble plaque sculpted with the words: KATASEMAS EMPORIUM.\n");
   add_item("shop",
       "It looks open to the west. A sign hangs over the entrance.\n");
   add_item(({"fresco","wall"}),
       "There is no entrance here to the building to the east, but a "+
       "fresco has been painted on the wall depicting a loaf of bread, "+
       "a bunch of grapes, and a lit lamp. You guess that is probably "+
       "part of the inn just to the north.\n");
 
   reset_room();
 
   /* exits */
   add_exit(ROOM_DIR+"droad8",  "north",0);
   add_exit(ROOM_DIR+"droad10", "south",0);
   add_exit(ROOM_DIR+"shop",    "west",0);
}
