/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 4
object npc=allocate(NUM);
 
void make_npc(int i) {
    string path;
    if (npc[i]) return;
    switch(i) {
       case 0:  path=KRCAMP_DIR+"monsters/dcomder/dcomder1";         break;
       case 1:  path=KRCAMP_DIR+"monsters/ensign/ensign0";           break;
       default: path=KRCAMP_DIR+"monsters/soldier/soldier1";         break;
    }
    npc[i]=clone_object(path);
    npc[i]->equip_me();
    npc[i]->move(THIS);
    tell_room(THIS, QCNAME(npc[i])+" steps out from behind a tree.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_npc(i);
}
 
/* room definition */
void create_room() {
   set_short("A dense forest");
   set_long(
       "A dense forest surrounds you on all sides, composed of towering " +
       "maples and stately oaks. Blooming dogwoods splash pink and white " +
       "throughout the dark forest. You can hear a squirrel chattering " +
       "somewhere in the trees. To the south, you see a marble road, " +
       "while a small path leads west through the forest.\n");
 
    add_item("road",   "It lies to the south.\n");
    add_item("forest", "It grows densely all around you.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"for3","west",0);
    add_exit(ROOM_DIR+"r19", "south",0);
    reset_room();
}
