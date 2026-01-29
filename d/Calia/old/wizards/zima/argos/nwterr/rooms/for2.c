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
    path=KRCAMP_DIR+"monsters/sentry/sentry1";
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
void create_room() {
   set_short("A dense forest");
   set_long(
       "A dense forest surrounds you on all sides, composed of towering " +
       "maples and stately oaks. Blooming dogwoods splash pink and white " +
       "throughout the dark forest, and you can hear the hoot of an owl " +
       "from the canopy of leaves. To the west, you see a marble road, " +
       "while a small path leads to the northwest and southeast.\n");
 
    add_item("road",   "It lies to the west.\n");
    add_item("forest", "It grows densely all around you.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"for1","northwest",0);
    add_exit(ROOM_DIR+"for3","southeast",0);
    add_exit(ROOM_DIR+"r16","west",0);
    reset_room();
}
