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
#include WRONGSTATUE
 
void create_room() {
   set_short("Portico of the Temple of Arxes");
   set_long(
      "You are standing on the portico of the Temple of Arxes "+
      "before the massive copper doors which mark the shrine's "+
      "entrance. A towering statue stands here atop a pedestal gazing out "+
      "over the city to the east, its presence filling you with a sense "+
      "of power. Enormous pillars line the edge of the portico, rising to "+
      "the heights of the ceiling where they are capped with impressive "+
      "capitols. A set of steps lead down to the road to the east, while "+
      "the portico runs to the north and south along the front of the "+
      "temple.\n");
 
   add_item("temple",
      "The temple is constructed of white marble with high walls which "+
      "seem to reach into the sky. Thick pillars line the face of the "+
      "temple, supporting the roof of the portico on which you are "+
      "standing. You marvel at the enormity of this fortress-like "+
      "shrine.\n");
   add_item("portico",
      "The portico is the covered area just outside the entrance "+
      "of the temple. Thick pillars line the edge of the portico, "+
      "supporting its roof above.\n");
   add_item(({"entrance","doors","door"}),
      "Two massive copper doors mark the high entrance of the temple "+
      "to the west, cast with the image of a large crested falcon "+
      "identical to the ones sculpted on the capitols of the pillars.\n");
   add_cmd_item(({"door","doors"}), ({"open","unlock"}),
      "The doors of the temple are sealed shut for now.\n");
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
      "the tree-like pillars.\n");
   add_item(({"view","city"}),
      "Looking out of the portico to the east lies the city of Argos, "+
      "with its one-level cubic commercial buildings to the north and "+
      "one of the city's large structures to the south.\n");
   add_item("steps","They lead down to the road to the east.\n");
   add_item("road","It is at the foot of the steps down to the east.\n");
   add_item("statue",
      "The statue is of a great warrior fully armoured for battle, "+
      "his plumed helmet fashioned in the form of the head of a "+
      "bird of prey. Beneath the armour he wears the robe of a priest. "+
      "He holds a large round shield in one hand, while the other rests "+
      "on the hilt of his sheathed broadsword. A falcon is perched on "+
      "his shoulder. He looks out over the city of Argos in a protective "+
      "manner, a gaze matched by that of his falcon.\n");
   add_item("pedestal",
      "The pedestal of the statue is a short block of marble, inlaid "+
      "with shiny copper details and lettering, including an "+
      "inscription written in large letters.\n");
   add_item("inscription",
      "It is written on the pedestal with bold copper letters. Perhaps "+
      "you can read it.\n");
   add_cmd_item("inscription","read",
      "It reads: ARXES - GOD OF POWER AND MIGHT - "+
      "PROTECTOR OF ALL THAT IS HOLY.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"port1","north",0);
   add_exit(ROOM_DIR+"port3","south",0);
   add_exit(METRO_DIR+"rooms/proad11","steps","@@steps");
}
 
void steps() {
    write( "You walk down the steps of the temple to the east onto "+
           "the road.\n");
   return 0;
}
