/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 4
object guard=allocate(NUM);
 
void make_guard(int i) {
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"guard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" steps out of the tent.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_guard(i);
}
 
void create_room() {
   set_short("A military camp");
   set_long(
       "A small tent stands amongst the trees of the forest to the west, "+
       "an outpost of the Argosian military in this area. This small camp "+
       "is no more than a clearing in the woods around the entrance to "+
       "the tent. A small path leads south through the trees, while the "+
       "entrance of the tent is open to the west.\n");
 
    add_item("path",
        "It is a small muddy path which leads south through the forest.\n");
    add_item("tent",
        "It is a small round tent with a cone-shaped top, made of canvas "+
        "of alternating blue and white stripes.\n");
    add_item(({"camp","campsite","site","clearing"}),
        "This small clearing in the forest along with the tent make up "+
        "a rather crude campsite.\n");
    add_item(({"forest","trees","woods"}),
        "Stately oaks and maples grow all around along the camp site, "+
        "interspersed with flowering " +
        "dogwoods, splashing pink and white in the shade of the " +
        "forest's canopy.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r25","south",0);
    add_exit(ROOM_DIR+"camptent","west",0);
    reset_room();
}
