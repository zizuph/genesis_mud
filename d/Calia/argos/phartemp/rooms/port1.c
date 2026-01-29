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
 
object priest;

void reset_room() {
   if (priest) return;
   priest=clone_object(NPC_DIR+"outpriest");
   priest->equip_me();
   priest->move(THIS);
   tell_room(THIS,QCTNAME(priest)+" walks onto the portico.\n");
}

void create_room() {
   set_short("Portico of the Temple of Pharos");
   set_long(
      "You are standing at the north end of the portico of the " +
      "temple of Pharos, enormous pillars supporting the roof of " +
      "the portico overhead. You have a wonderful view of the city "+
      "out to the west from this elevated height, though the intricate "+
      "details of a fresco painted on the ceiling of the portico hold your "+
      "attention. A set of steep steps leads down to the road to the "+
      "west, while the portico continues along the face of the "+
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
      "The capitols are ringed with doves which seem to be in a dive, "+
      "their heads pointed down and their tails up. Though they are "+
      "sculpted of marble, they seem almost life-like, frolicing "+
      "in the air.\n");
   add_item(({"roof","ceiling"}),
      "The roof of the portico rises high above you, supported by "+
      "the tree-like pillars. A detailed fresco is painted on the "+
      "ceiling.\n");
   add_item("fresco",
      "Painted with bright colors, the fresco portrays a priest wearing "+
      "a long sleeveless robe kneeling on the ground, holding the "+
      "body of a dead king in his arms. The priest's face expresses "+
      "the sadness of his heart.\n");
   add_item(({"view","city"}),
      "Looking out of the portico to the west lies the city of Argos, "+
      "with its one-level cubic commercial building to the north and "+
      "one of the Amphitheatre to the south.\n");
   add_item("steps","They lead down to the road to the west.\n");
   add_item("road","It is at the foot of the steps down to the west.\n");
   add_item("statue",
      "It is to the south on the portico. You could get a better look "+
      "if you went closer.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"port2","south",0);
   add_exit(METRO_DIR+"rooms/troad10","steps","@@steps");

   reset_room();
}
 
int steps() {
    write( "You walk down the steps of the temple to the west onto "+
           "the road.\n");
   return 0;
}
