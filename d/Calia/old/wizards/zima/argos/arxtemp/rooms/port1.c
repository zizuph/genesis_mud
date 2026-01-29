/* Temple of Arxes - Portico
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
   set_short("Portico of the Temple of Arxes");
   set_long(
      "You are standing at the north end of the portico of the " +
      "temple of Arxes, enormous pillars supporting the roof of " +
      "the portico overhead. You have a wonderful view of the city "+
      "out to the east from this elevated height, though the intricate "+
      "details of a fresco painted on the ceiling of the portico hold your "+
      "attention. A set of steep steps leads down to the road to the "+
      "east, while the portico continues along the face of the "+
      "temple to the south, where you see a towering statue.\n");
 
   add_item("temple",
      "The temple is constructed of white marble with high walls which "+
      "seem to reach into the sky. Thick pillars line the face of the "+
      "temple, supporting the roof of the portico on which you are "+
      "standing. You marvel at the enormity of this fortress-like "+
      "shrine.\n");
   add_item("portico",
      "The portico is the covered area just outside the entrance "+
      "of the temple. Thick pillars line the edge of the portico, "+
      "supporting its roof above. The ceiling is painted with "+
      "a detailed fresco, while a towering statue stands on "+
      "the portico further south.\n");
   add_item("entrance","You see an entrance to the temple further south.\n");
   add_item("pillars",
      "The pillars are made of the same white marble as the temple, "+
      "lined along the edge of the portico supporting its roof. "+
      "The massive trunks of the pillars are thicker than most any "+
      "tree you have ever seen. Elaborate capitols decorate the tops "+
      "of each pillar.\n");
   add_item("capitols",
      "The capitols are ringed with falcons, the shoulders of their "+
      "wings near their heads with the tips fanned down to their "+
      "claws. Their ferocious eyes and sharp beaks make them look "+
      "almost like monstrous guardians looking over the portico.\n");
   add_item(({"roof","ceiling"}),
      "The roof of the portico rises high above you, supported by "+
      "the tree-like pillars. A detailed fresco is painted on the "+
      "ceiling.\n");
   add_item("fresco",
      "Painted with bold colors, the fresco portrays a battle scene "+
      "in which armoured priests with red capes are meeting a horde "+
      "of warriors dressed similarly with black clothing. Above the "+
      "battlefield of men, falcons battle with ravens in the smoky "+
      "sky.\n");
   add_item(({"view","city"}),
      "Looking out of the portico to the east lies the city of Argos, "+
      "with its one-level cubic commercial buildings to the north, and "+
      "one of the city's large structures to the south.\n");
   add_item("steps","They lead down to the road to the east.\n");
   add_item("road","It is at the foot of the steps down to the east.\n");
   add_item("statue",
      "It is to the south on the portico. You could get a better look "+
      "if you went closer.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"port2","south",0);
   add_exit(METRO_DIR+"rooms/proad10","steps","@@steps");
}
 
void steps() {
    write( "You walk down the steps of the temple to the east onto "+
           "the road.\n");
   return 0;
}
