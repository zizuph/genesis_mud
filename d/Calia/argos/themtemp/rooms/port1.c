/* Temple of Thema - Portico
**
** History:
** Date        Coder       Action
** ----------- ----------- --------------------------------------
** 8/25/95     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Portico of the Temple of Thema");
   set_long(
      "You are standing on the west end of the portico of the " +
      "Temple of Thema before one of the entrances of the shrine. "+
      "Tall pillars support the roof of the portico overhead, where "+
      "you see a fresco painted in somber colors on the ceiling. "+
      "You have a wonderful view of the city from this elevated height "+
      "as you gaze out toward the south. A set of steep steps leads down "+
      "to the road, while the portico continues along the face of the "+
      "temple to the east where you see an imposing statue.\n");
 
   add_item("temple",
      "The temple is constructed of white marble with high walls which "+
      "seem to reach into the sky. Tall pillars line the face of the "+
      "temple, supporting the roof of the portico on which you are "+
      "standing. You marvel at the splendor of this sacred structure.\n");
   add_item("portico",
      "The portico is the covered area just outside the entrance "+
      "of the temple. Tall pillars line the edge of the portico, "+
      "supporting its roof above. The ceiling is painted with "+
      "a detailed fresco, while an imposing statue stands on "+
      "the portico further east.\n");
   add_item("entrance",
      "There is an entrance to the temple here which would lead north "+
      "into the shrine; however, it is barred by a large brass door.\n");
   add_item("door",
      "It is a large door made of brass, cast with three perched owls "+
      "from top to bottom.\n");
   add_cmd_item("door",({"unlock","open"}),
      "The door of the temple is sealed for now.\n");
   add_item("pillars",
      "The pillars are made of the same white marble as the temple, "+
      "lined along the edge of the portico supporting its roof. "+
      "The tall trunks of the pillars are rise high above your head. "+
      "Elaborate capitols decorate the tops of each pillar.\n");
   add_item("capitols",
      "The capitols are sculpted with perched owls sitting in a ring "+
      "around the top of each pillar. The large round eyes of the "+
      "birds seem to watch all that happens here.\n");
   add_item(({"roof","ceiling"}),
      "The roof of the portico rises high above you, supported by "+
      "the tree-like pillars. A detailed fresco is painted on the "+
      "ceiling.\n");
   add_item("fresco",
      "Painted with somber colors, the fresco portrays a host of "+
      "priestesses, all dressed in long white robes, their hair in "+
      "one long braid in the back, adoring a central figure, a female "+
      "diety adorned similarly but larger than life.\n");
   add_item(({"view","city"}),
      "Looking out of the portico to the south lies the city of Argos, "+
      "the one-level cubic commercial buildings lining the streets "+
      "in all directions.\n");
   add_item("steps","They lead down to the road to the south.\n");
   add_item("road","It is at the foot of the steps down to the south.\n");
   add_item("statue",
      "It is to the east on the portico. You could get a better look "+
      "if you went closer.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"port2","east",0);
   add_exit(METRO_DIR+"rooms/lroad11","steps","@@steps");
}
 
void steps() {
   write("You walk down the steps of the temple to the south.\n");
   return 0;
}
