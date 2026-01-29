/*
**   ARGOS - Metro - Library - east end of hallway
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/5/95     Zima       Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"
#include TOEQUEST
 
void create_room() {
   set_short("Library of Argos");
   set_long(
      "You are in the grand hall of the Library of Argos, an enormous "+
      "chamber of sparkling gray marble dominated by an impressive "+
      "statue standing on a pedestal. Large entrances to other chambers "+
      "lead out to the north and south, while the grand hall continues "+
      "further west. Two large pillars mark the exit from the building "+
      "to the east.\n");
 
   add_item("statue",
      "It is the statue of a regal man with a boyish face, aged only "+
      "by a short-trimmed beard. The figure wears a long flowing "+
      "robe with a scholarly hood hanging down his back. He holds "+
      "a scroll in both hands.\n");
   add_item(({"toe","toe of statue","toe on statue"}),
       "The toe of the king looks highly polished compared to "+
       "the rest of the statue.\n");
 
   add_item("pedestal",
      "It is a cubic block of glassy gray marble, matching that "+
      "of the walls and floor, on which the statue stands. An "+
      "inscription is etched into the face of the pedestal.\n");
   add_item("inscription",
      "It is etched into the face of the pedestal. Perhaps you "+
      "can read it.\n");
   add_cmd_item("inscription","read",
      "It reads: BIBLIONUS : EIGHTH MONARCH OF ARGOS : 222 - 266.\n");
   add_item(({"hall","chamber","walls","floor"}),
      "The hall is constructed of gray marble which seems to be coated "+
      "in glass, the walls and floor reflecting the colorful light "+
      "from the hall further west.\n");
   add_item("entrances","Wide entrances open up into other chambers "+
      "to the north and south.\n");
   add_item("pillars","They stand like sentinels guarding the exit "+
      "from the building to the east.\n");
 
   /* room properties */
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"lib2","north",0);
   add_exit(ROOM_DIR+"lib4","south",0);
   add_exit(ROOM_DIR+"droad13","east",0);
   add_exit(ROOM_DIR+"libhall1","west",0);
   toe_quest_set_statue_prop(TOE_QUEST_BIBLIONUS);
}
