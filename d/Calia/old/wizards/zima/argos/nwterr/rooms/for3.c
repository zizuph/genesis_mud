/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 3
object *npc=allocate(NUM);
 
void make_npc(int i) {
    string path;
    if (npc[i]) return;
    path=KRCAMP_DIR+"monsters/soldier/soldier1";
    npc[i]=clone_object(path);
    npc[i]->equip_me();
    npc[i]->move(THIS);
    tell_room(THIS, QCNAME(npc[i])+" steps out from the trees.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_npc(i);
}
 
/* room definition */
void
create_room()
{
   set_short("A dense forest");
   set_long(break_string(
       "A dense forest surrounds you on all sides, composed of towering " +
       "maples and stately oaks.  Blooming dogwoods splash pink and white " +
       "throughout the dark forest.  There is a disturbing silence in " +
       "this part of the woods.  To the west, you see a marble road, " +
       "while a small path leads to the northwest and east.\n",70));
 
    add_item("road",   "It lies to the west.\n");
    add_item("forest", "It grows densely all around you.\n");
 
 
    /* exits */
    add_exit(ROOM_DIR+"for2","northwest",0);
    add_exit(ROOM_DIR+"for4","east",0);
    add_exit(ROOM_DIR+"r17", "west",0);
    reset_room();
}
