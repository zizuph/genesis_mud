/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 3
object npc=allocate(NUM);
 
void make_npc(int i) {
    string path;
    if (npc[i]) return;
    switch(i) {
       case 0:  path=KRCAMP_DIR+"monsters/tcomder/tcomder1";         break;
       default: path=KRCAMP_DIR+"monsters/soldier/soldier1";         break;
    }
    npc[i]=clone_object(path);
    npc[i]->equip_me();
    npc[i]->move(THIS);
    tell_room(THIS, QCNAME(npc[i])+" steps out of the forest.\n");
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
       "throughout the dark forest. To the west, you can see the back "+
       "of a dwelling, but the forest is too thick to walk that way. You "  +
       "see a marble road to the south, while a small path leads east " +
       "into the forest.\n");
 
    add_item("road",   "It lies to the south.\n");
    add_item("forest", "It grows densely all around you.\n");
    add_item("dwelling",
             "You can barely see the back of it through the trees.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"for6","east",0);
    add_exit(ROOM_DIR+"r21", "south",0);
    reset_room();
}
