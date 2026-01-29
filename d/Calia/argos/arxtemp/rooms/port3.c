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
      "A breathtaking view of the city presents itself as you gaze "+
      "out to the east from the porctico of the Temple of Arxes. "+
      "Enormous pillars line the edge of the portico like sentinels "+
      "supporting its roof overhead, where a detailed fresco has been "+
      "artfully painted on the ceiling. A set of steps leads down "+
      "to the road to the east, while you can walk along the portico "+
      "to the north where a statue is standing.\n");
 
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
      "the portico further north.\n");
   add_item("entrance","You see an entrance to the temple further north.\n");
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
      "Painted with bold colors, the fresco portrays armoured priests "+
      "with red capes carefully maneuvering their way through a forest "+
      "of dark pines. Falcons swoop from limb to limb among the pines, "+
      "hovering over the armed host like a protective cloud.\n");
   add_item(({"view","city"}),
      "Looking out of the portico to the east lies the city of Argos, "+
      "with its one-level cubic commercial buildings to the north and "+
      "one of the city's large structures to the south.\n");
   add_item("steps","They lead down to the road to the east.\n");
   add_item("road","It is at the foot of the steps down to the east.\n");
   add_item("statue",
      "It is to the north on the portico. You could get a better look "+
      "if you went closer.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"port2","north",0);
   add_exit(METRO_DIR+"rooms/proad12","steps","@@steps");
}
 
void steps() {
    write( "You walk down the steps of the temple to the east onto "+
           "the road.\n");
   return 0;
}
