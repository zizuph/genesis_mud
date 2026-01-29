/* ARGOS - SWTERR - Dirt road along south bank of river
**
** History:
** Date      Coder      Action
** --------- ---------- --------------------------------
** 11/10/95  Zima       Created
** 8/16/96   Zima       added special exit into kretan camp area
**
*/
/* inherits/includes */
inherit  "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 2
object *woodsman=allocate(NUM);
int enter();
void make_monster(int i) {
    if (woodsman[i]) return;
    woodsman[i]=clone_object(NPC_DIR+"woodsman");
    woodsman[i]->equip_me();
    woodsman[i]->move(THIS);
    tell_room(THIS, QCNAME(woodsman[i])+" emerges from the forest.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
void create_room() {
   set_short("A dirt road along a river");
   set_long(
      "A dark and forboding forest of black pines rises high above you to "+
      "the west, its thick branches of sharp needles discouraging entrance "+
      "into its dark depths. "+
      "To the east across the river sits a large temple, where you see a "+
      "portico which extends into the river's bend here. The dusty road "+
      "leads around the bend of the river to the northeast and southeast.\n");
 
   add_item(({"forest","pines","trees"}),
      "A dark forest of towering pines grows thickly to the west, the long "+
      "needles of the trees looking sharp enough to draw blood. The branches "+
      "of the trees, with their sharp needles, forewarn any who would enter "+
      "of the consequences of their action.\n");
   add_item(({"needles","branches"}),
      "The branches of the trees are covered with sharp needles, sure to "+
      "prick the bear skin of any creature that might try to crawl through "+
      "them.\n");
   add_cmd_item("through branches","crawl","@@enter");
   add_item("road",
      "A simple dirt road, newly cleared through the forest, which " +
      "follows a river along its western bank.\n");
   add_item(({"city","Argos","argos"}),
      "The city lies on the eastern side of the river, where you see an "+
      "enormous temple.\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. " +
      "It provides a great amount of protection for the city of Argos "+
      "which is built on its eastern side.\n");
   add_item(({"walls","temple"}),
       "A large temple made of brilliant white marble sits across the "+
       "river to the east, its high walls serving as a fortress to any "+
       "which might successfully cross the river, which would be doubtful.\n");
   add_item("portico",
       "It is a long rectangular extension on the face of the temple, "+
       "a row of pillars lining its front.\n");
   reset_room();
 
   /* exits */
   add_exit(ROOM_DIR+"r28","northeast",0);
   add_exit(ROOM_DIR+"r30","southeast",0);
}
 
int enter() {
   write("You crawl through the branches, sharp needles scratching " +
         "your hands and face painfully.\n");
   this_player()->move_living("into the sharp-needled branches",
                              KRCAMP_DIR+"rooms/npath6");
   return 1;
}
