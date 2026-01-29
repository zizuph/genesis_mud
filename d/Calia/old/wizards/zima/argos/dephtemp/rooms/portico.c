/* Portico (front porch) of the Temple of Dephonia
**
** History:
** Date        Coder       Action
** 1/10/95     Zima        Created
**
** NOTE: This is the "front door" of the temple, with the temple closed.
**       To open the temple, copy PORTICO.OPEN to PORTICO.C and
**       update PORTICO.C. This will effectively OPEN the temple.
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "vqscenes.h"
 
#define NUM 3
#define SCENE_NUM 12
object *priest=allocate(NUM);
 
void make_monster(int i) {
    if (priest[i]) return;
    priest[i]=clone_object(NPC_DIR+"porguard");
    priest[i]->equip_me();
    priest[i]->move(THIS);
    tell_room(THIS, QCNAME(priest[i])+" walks onto the portico.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
}
 
void create_room() {
   set_short("Portico of the Temple of Dephonia");
   set_long(
      "You step onto the portico of the black temple, a structure " +
      "which provides a covered entrance into the hidden shrine. " +
      "Towering pillars support the ceiling of the portico, arranged " +
      "around its rectangular edges. There are two massive doors " +
      "to the temple here on its northern corner, tall bronze " +
      "gates cast with highly-detailed figures. An inscription has " +
      "been hewn into the marble above the entrance. " +
      "A fresco is painted " +
      "on the ceiling of the roof which shades the entrance from " +
      "the sunlight. A set of steep steps leads down from the " +
      "portico into a clearing in the surrounding forest.\n");
 
    add_item("temple",
      "It is an enromous ancient structure with a rows of pillars " +
      "lining its outer walls. This rectangular portico has been built " +
      "on the northern end of the diamond-shaped monolith as a covering " +
      "for the temple's entrance. The darkness " +
      "of the temple walls seems to absorb even the sunlight.\n");
 
    add_item("portico",
      "It is a rectangular appendage built onto the northern corner " +
      "of the temple, tall pillars supporting its roof. It covers " +
      "the entrance to the mysterious black structure.\n");
 
    add_item("inscription",
      "Hewn into the marble above the doors with large letters, " +
      "the inscription reads: NAOS DEPHONIA.\n");
 
    add_item(({"doors","gates"}),
      "Towering high above your head, the thick heavy doors are cast " +
      "of bronze and are embellished with mysterious figures. They "+
      "stand open allowing entrance to the temple to the south.\n");
    add_cmd_item(({"doors","gates"}), ({"open","unlock"}),
      "The doors of the temple are sealed and can not be opened.\n");
 
    add_item("figures",
      "Molded into the face of the towering doors of the temple, " +
      "these strange figures depict a large gathering of people, " +
      "their backs to you, an audience for a beautiful goddess " +
      "who stands facing you in their midst. Her face is turned " +
      "down and to the side, an evil loving smile on her face.\n");
 
    add_item(({"roof","fresco","ceiling"}),
       "As you stare up into the heights of the the portico, you see " +
       "a fresco painted on the ceiling. It depicts "+
       vq_scene[SCENE_NUM]+". A banner beneath the fresco has "+
       "some words written on it.\n");
 
   add_item(({"banner","words"}),
      "A banner is painted beneath the fresco on the ceiling with "+
      "some words written on it. Perhaps you can read the words.\n");
 
   add_cmd_item("words","read",
      "They read: "+vq_prayer[SCENE_NUM]+".\n");
 
   add_item("pillars",
      "Massive columns of black marble, topped with elaborate capitals " +
      "which are hewn into the image of writhing snakes, they line " +
      "the outer walls of the temple on all sides and support the " +
      "roof of the portico above the entrance.\n");
 
   add_item("steps",
      "A steep set of short steps lead down to a clearing in " +
      "the forest.\n");
 
   add_item("entrance",
      "It is to the south, on the northern corner of the temple, " +
      "marked by two enormous bronze doors.\n");
 
   add_item(({"forest","trees","branches"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
 
   add_item("path", "It leads north back into the forest.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"courtyrd","steps","@@steps");
   add_exit(ROOM_DIR+"foyer","south",0);
   reset_room();
}
 
void steps() {
    write(break_string(
          "You walk down the steep steps of the temple, almost " +
          "slipping on the glassy black marble.\n",70));
   return 0;
}
