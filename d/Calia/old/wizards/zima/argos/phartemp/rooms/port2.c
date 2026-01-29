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
#include WRONGSTATUE
 
void create_room() {
   set_short("Portico of the Temple of Pharos");
   set_long(
      "You are standing on the portico of the Temple of Pharos "+
      "before the massive silver doors which mark the shrine's "+
      "entrance. A towering statue stands here atop a pedestal gazing out "+
      "over the city to the east, its presence filling you with a sense "+
      "of peace. Enormous pillars line the edge of the portico, rising to "+
      "the heights of the ceiling where they are capped with impressive "+
      "capitols. A set of steps lead down to the road to the west, while "+
      "the portico runs to the north and south along the front of the "+
      "temple.\n");
 
   add_item("temple",
      "The temple is constructed of white mar high walls which "+
      "seem to reach into the sky. Thick pillars line the face of the "+
      "temple, supporting the roof of the portico on which you are "+
      "standing. You marvel at the enormity of this fortress-like "+
      "shrine.\n");
   add_item("portico",
      "The portico is the covered area just outside the entrance "+
      "of the temple. Thick pillars line the edge of the portico, "+
      "supporting its roof above.\n");
   add_item(({"entrance","doors","door"}),
      "Two massive silver doors mark the high entrance of the temple "+
      "to the east, cast with the image of a large dove in flight, "+
      "similar to the ones sculpted on the capitols of the pillars.\n");
   add_cmd_item(({"door","doors"}), ({"open","unlock"}),
      "The doors of the temple are sealed shut for now.\n");
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
      "the tree-like pillars.\n");
   add_item(({"view","city"}),
      "Looking out of the portico to the west lies the city of Argos, "+
      "with its one-level cubic commercial building to the north and "+
      "one of the Amphitheatre to the south.\n");
   add_item("steps","They lead down to the road to the west.\n");
   add_item("road","It is at the foot of the steps down to the west.\n");
   add_item("statue",
      "The statue is of a young man dressed in a long sleeveless robe "+
      "belted with a simple rope. He has curly hair capped with a small "+
      "wreath of olive leaves, and a boyish, "+
      "loving face that would capture the heart of any mother. He "+
      "holds a dove in his hands, his gentle gaze cast lovingly "+
      "on the bird. His expression seems to portray an ancient and "+
      "yet youthful demeanour.\n");
   add_item("pedestal",
      "The pedestal of the statue is a short block of marble, inlaid "+
      "with glittering silver details and lettering, including an "+
      "inscription written in large letters.\n");
   add_item("inscription",
      "It is written on the pedestal with bold silver letters. Perhaps "+
      "you can read it.\n");
   add_cmd_item("inscription","read",
      "It reads: PHAROS - GOD OF LIFE AND HEALING - "+
      "THE GIVER OF LIFE AND LOVE.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"port1","north",0);
   add_exit(ROOM_DIR+"port3","south",0);
   add_exit(METRO_DIR+"rooms/troad11","steps","@@steps");
}
 
int steps() {
    write( "You walk down the steps of the temple to the west onto "+
           "the road.\n");
   return 0;
}
