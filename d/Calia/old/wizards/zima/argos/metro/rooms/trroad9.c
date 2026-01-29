/*
** ARGOS - Metro - Tritos Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "toequest.c"
#define NUM 2
object *citizen=allocate(NUM);
 
void make_monster(int i) {
    if (citizen[i]) return;
    citizen[i]=clone_object(NPC_DIR+"citizen");
    citizen[i]->equip_me();
    citizen[i]->move(THIS);
    tell_room(THIS, QCTNAME(citizen[i])+" walks down the road.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
 
void create_room() {
   set_short("Tritos Road");
   set_long(
       "A tall statue standing on a pedestal sits in the center of Tritos "+
       "road here, dominating this part of the commercial district. "+
       "To the west is a building with a facade covered "+
       "with an enormous relief, while another of the city's businesses "+
       "is open to the east, a sign hanging next to its entrance. Tritos "+
       "road continues north and south through the district.\n");
   add_cmd_item("sign","read","It reads: SIDERAS FORGE.\n");
 
   add_item("road",
            "It leads north and south through the commercial district.\n");
   add_item(({"district","commercial district"}),
            "The commercial district is made up of rows of one-level "+
            "buildings which house the business of the city.\n");
   add_item(({"shops","establishments","buildings","enterprises"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the both sides like white cubes.\n");
   add_item(({"building","facade","relief"}),
      "The facade of the building to the west is covered completely by "+
      "a relief which depicts various artisans at their work. The "+
      "figures make the facade of the building look busy, but it "+
      "is some of the best sculpture you have seen in the city.\n");
   add_item("business",
      "It is open to the east. A sign hangs next to its entrance.\n");
   add_item("sign",
      "It is a simple wooden sign with metal letters bolted into it. "+
      "The sign reads: SIDERAS FORGE.\n");
   add_item("statue",
      "The statue is of a square-jawed man dressed in a stylized "+
      "tunic and a long flowing cloak. The regal figure is wearing "+
      "a crown with three jewels on his head, and holds what a sickle "+
      "in one hand and a long thin paint brush in the other. He seems "+
      "to gaze protectingly over this part of the district.\n");
   add_item("pedestal",
      "The pedestal is a large block of marble, its sides intricately "+
      "sculpted branches of olive trees. There is an inscription written "+
      "in bold letters on each its four sides.\n");
   add_item("inscription",
      "It is written in bold letters on all four sides of the statue's "+
      "pedestal. Perhaps you can read it.\n");
   add_cmd_item("inscription","read",
      "It reads: AGRARIUS : THIRD MONARCH OF ARGOS : 64-89 AT.\n");
   add_item(({"toe","toe of statue","toe on statue"}),
       "The toe of the king looks highly polished compared to "+
       "the rest of the statue.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"trroad8","north",0);
   add_exit(ROOM_DIR+"trroad10","south",0);
   add_exit(ROOM_DIR+"forge","east",0);
   add_exit(ROOM_DIR+"sculptor", "west",0);
   toe_quest_set_statue_prop(TOE_QUEST_AGRARIUS);
   reset_room();
}
