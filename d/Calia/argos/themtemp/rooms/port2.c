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
#include WRONGSTATUE
 
void create_room() {
   set_short("Portico of the Temple of Thema");
   set_long(
      "You are standing on the portico of the Temple of Thema "+
      "amongst the tall pillars which support its roof. "+
      "An imposing statue of a goddess stands on top of a pedestal "+
      "here, her gaze sweeping the view of the city to the south. "+
      "A relief has been sculpted into the wall of the temple to the "+
      "north behind the statue. A set of steep steps leads down "+
      "to the road to the south, while you may walk along the face "+
      "of the temple on the portico to the east and west.\n");
 
   add_item("temple",
      "The temple is constructed of white marble with high walls which "+
      "seem to reach into the sky. Tall pillars line the face of the "+
      "temple, supporting the roof of the portico on which you are "+
      "standing. A relief is sculpted into the wall of the temple.\n");
   add_item("portico",
      "The portico is the covered area just outside the entrance "+
      "of the temple. Tall pillars line the edge of the portico, "+
      "supporting its roof above. It continues to the east and "+
      "west where you see entrances to the shrine.\n");
   add_item(({"entrance","entrances"}),
      "You see none here, but there is one to the west and to the east.\n");
   add_item("relief",
      "Sculpted into the wall of the temple, the relief is of a large "+
      "owl with penetrating round eyes, perched on a branch with "+
      "oak leaves. The details of the feathers and eyes make the bird "+
      "look almost alive, though a hundred times larger than any owl "+
      "you have ever seen.\n");
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
      "the tree-like pillars.\n");
   add_item(({"view","city"}),
      "Looking out of the portico to the south lies the city of Argos, "+
      "the one-level cubic commercial buildings lining the streets "+
      "in all directions.\n");
   add_item("steps","They lead down to the road to the south.\n");
   add_item("road","It is at the foot of the steps down to the south.\n");
   add_item("statue",
      "It is a statue of a goddess wearing a long flowing robe belted "+
      "with a simple rope. Her hair is braided into a long braid "+
      "which falls down her back almost to her feet. She holds an "+
      "oak leaf in her hands as if it has a scent like a flower. "+
      "Her face is smooth and motherly, but her eyes portray great "+
      "wisdom. An owl is perched on her shoulder, its large round "+
      "eyes gazing out over the city.\n");
   add_item("pedestal",
      "It is a large block of marble detailed and lettered with gold. "+
      "A large inscription is written across the front in gold letters.\n");
   add_item("inscription",
      "It is written in gold letters on the pedestal. Perhaps you can "+
      "read it.\n");
   add_cmd_item("inscription","read",
      "It reads: THEMA - GODDESS OF WISDOM - PRESERVER OF KNOWLEDGE.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"port1","west",0);
   add_exit(ROOM_DIR+"port3","east",0);
   add_exit(METRO_DIR+"rooms/lroad12","steps","@@steps");
}
 
int steps() {
   write( "You walk down the steps of the temple to the south.\n");
   return 0;
}
