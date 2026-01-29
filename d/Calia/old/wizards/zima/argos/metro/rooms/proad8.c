/*
**   ARGOS - Metro - Protos Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Protos Road");
   set_long(
       "You are walking down Protos road on the west side of town. "+
       "One of the city's large temples sits to the west, a monument to "+
       "the deity for whom it was built. Shops and other commercial "+
       "establishments line the road on the east side, a blue flag "+
       "hanging next to the entrance of the one to the east.\n");
 
   add_item(({"building","shop","establishment"}),
       "It is one of the buildings of the commercial district, a "+
       "simple cube of marble. A blue flag hangs next to the entrance.\n");
   add_item("flag",
       "It is hanging from a pole which angles from its base on "+
       "the wall of the building to the east. It is made of blue "+
       "silk and bears the royal arms, a shield emblazoned with a "+
       "winged horse surmounted by a crown with three jewels.\n");
   add_item(({"road","roads","street","streets"}),
       "Protos road runs north and south between a temple and a row "+
       "of commercial buildings.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the east side like white cubes.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. You don't seen an entrance to it "+
       "here.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"lroad7",  "north",0);
   add_exit(ROOM_DIR+"proad9",  "south",0);
   add_exit(ROOM_DIR+"visitctr","east",0);
}
