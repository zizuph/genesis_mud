/*
**   ARGOS - Metro - Chiphas Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/5/95     Zima       Created
**   5/12/16    Jaacar     Fixed typo
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Chiphas Road");
   set_long(
       "An ornate building stands open to the north in the row of "+
       "shops and other businesses which line the Chiphas road on "+
       "that side. A seal has been sculpted into the wall of "+
       "of the building, while an inscription is written above the "+
       "entrance in bold lettering. One of the city's large marble "+
       "structures sits south of the road, a relief of figures sculpted "+
       "into the triangular end of its roof.\n");
 
   add_item(({"building","shop","establishment"}),
       "It is an official-looking building of shining white marble, its "+
       "walls bordered in blue tile. There is an entrance to it to the "+
       "north between two pillars which buttress the doorway.\n");
   add_item("pillars",
       "They mark the entrance to the building to the north.\n");
   add_item(({"wall","seal"}),
       "It is a shield emblazoned with a rampant winged horse surmounted "+
       "by a crown with three jewels. Two large keys are crossed in an X "+
       "shape behind the shield of the emblem.\n");
   add_item("inscription",
       "Sculpted in bold letters in the marble above the entrance to "+
       "the building, the insription reads: ROYAL BANK OF ARGOS.\n");
   add_cmd_item("inscription","read","It reads: ROYAL BANK OF ARGOS.\n");
   add_item(({"road","roads","street","streets"}),
       "Chipas road runs east and west between a large structure and a "+
       "row of commercial buildings.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the north side like white cubes.\n");
   add_item("structure",
       "It a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"roof","relief"}),
       "The figures of many heroic Argosians garbed in their traditional "+
       "tunics are sculpted into a relief on the triangular end of the "+
       "roof of the large building.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"bank","north",0);
   add_exit(ROOM_DIR+"croad8","west",0);
   add_exit(ROOM_DIR+"droad11", "east",0);
}
