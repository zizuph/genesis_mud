/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 11/18/96 Zima             Created
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  NUM 3
 
object guard=allocate(NUM);
 
void make_guard(int i) {
   if (guard[i]) return;
   guard[i]=clone_object(NPC_DIR+"bguard");
   guard[i]->equip_me();
}
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_guard(i);
}
 
void create_room() {
   set_short("An outpost on a marble road");
   set_long(
     "This stretch of road seems to be a border outpost, set along side "+
     "the river. To the east is a covered station, marble pillars holding "+
     "aloft its flat roof, it almost looks like an unwalled temple. "+
     "An arched bridge spans the river to the west, leading to the other "+
     "bank, while the marble road follows the rivers path as it bends "+
     "to the southeast. There is a narrow path leading north into the "+
     "dense forest.\n");
 
   add_item("path",
      "It is a narrow path trodden through the trees. It leads into the "+
      "depths of the forest to the north.\n");
   add_item("station",
      "It is a large platform set in a clearing of the forest. Marble "+
      "pillars rise from its floor to hold up a flat marble roof, a "+
      "bit of shelter from the rain. It seems to be some sort of depot.\n");
   add_item("pillars",
      "They stand like trees along the edge of the station's platform, "+
      "supporting its roof.\n");
   add_item("roof",
      "The roof of the station is made of flat panels of marble, "+
      "supported by the pillars.\n");
   add_item("bridge",
      "It is an arched bridge made of white marble, skillfully sculpted "+
      "as both a work of art and a passage across the river. It looks "+
      "fairly new.\n");
   add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "It flows from the foothills to the north, into the valley to "+
       "the southeast. A marble bridge spans its banks.\n");
   add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It leads west across the bridge and southeast along the " +
       "river's bank.\n");
   add_item("mountains",
       "Looming along the western horizon, the mountains seem high but " +
       "passable along the marble road.\n");
   add_item(({"forest","maples","oaks","evergreens","trees"}),
       "A mixture of maples, oaks and evergreens, the forest grows "+
       "densly on either side of the road.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"mbridge","west",0 );
   add_exit(ROOM_DIR+"r14b","southeast",0);
   add_exit(ROOM_DIR+"depotout","east",0);
   add_exit(ROOM_DIR+"sfor1","north",0);
}
