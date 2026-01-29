/* Temple of Pharos - Portico
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
   set_short("Portico of the Temple of Pharos");
   set_long(
      "This is the portico of the Temple of Pharos, one of the great "+
      "shrines of the city of Argos. "+
      "Enormous pillars rise high above your head to the ceiling "+
      "of the portico on which you are standing, where you see a "+
      "fresco painted on the ceiling in bright colors. A set of steps "+
      "lead down to the road to the west, where you can see an excellent "+
      "view of the city. The portico extends to the north along the "+
      "face of the temple, where you see a statue standing.\n");
 
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
   add_item("entrance","You see an entrance to the temple further north.\n");
   add_item("pillars",
      "The pillars are made of the same white marble as the temple, "+
      "lined along the edge of the portico supporting its roof. "+
      "The massive trunks of the pillars are thicker than most any "+
      "tree you have ever seen. Elaborate capitols decorate the tops "+
      "of each pillar.\n");
   add_item("capitols",
      "The capitols are ringed with doves which seem to be in a dive, "+
      "their heads pointed down and their tails up. Though they are "+
      "sculpted of marble, they seem almost life-like, frolicing "+
      "in the air.\n");
   add_item(({"roof","ceiling"}),
      "The roof of the portico rises high above you, supported by "+
      "the tree-like pillars. A detailed fresco is painted on the "+
      "ceiling.\n");
   add_item("fresco",
      "Painted with bright colors, the fresco portrays a priestess "+
      "in the woods caring for an injured beast. She holds her hand "+
      "over its head and seems to be mumbling a prayer. A dove sits "+
      "on a branch of a nearby tree watching over the scene.\n");
   add_item(({"view","city"}),
      "Looking out of the portico to the west lies the city of Argos, "+
      "with its one-level cubic commercial building to the north and "+
      "one of the Amphitheatre to the south.\n");
   add_item("steps","They lead down to the road to the west.\n");
   add_item("road","It is at the foot of the steps down to the west.\n");
   add_item("statue",
      "It is to the north on the portico. You could get a better look "+
      "if you went closer.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"port2","north",0);
   add_exit(METRO_DIR+"rooms/troad12","steps","@@steps");
}
 
int steps() {
    write( "You walk down the steps of the temple to the west onto "+
           "the road.\n");
   return 0;
}
