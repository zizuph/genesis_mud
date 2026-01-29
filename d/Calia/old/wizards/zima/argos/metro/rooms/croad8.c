/*
**   ARGOS - Metro - Chiphas Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/5/95     Zima       Created
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
       "You are walking down Chiphas road between the city's commercial "+
       "district to the north and a large building to the south. A "+
       "unique sign hangs above the entrance of the shop to the north, "+
       "one of the many one-level structures which house the local "+
       "businesses. You admire a "+
       "relief sculpted into the flat-triangular end of the roof "+
       "of the grand structure to your south.\n");
 
   add_item(({"building","shop","establishment"}),
       "It is one of the buildings of the commercial district, a "+
       "simple cube of marble. There seems to be a light but noticeable "+
       "stench coming from the building. A unique sign hangs above its "+
       "entrance.\n");
   add_item("sign",
       "The wooden sign is carved in the shape of a pigeon. There is no "+
       "lettering on it, but the details of the fowl are colorfully "+
       "painted.\n");
   add_cmd_item("sign","read","There is nothing on the sign to read.\n");
   add_item(({"road","roads","street","streets"}),
       "Chipas road runs east and west between a large structure and a "+
       "row of commercial buildings.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the north side like white cubes.\n");
   add_item(({"building","structure"}),
       "It a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"roof","relief"}),
       "The figures of many heroic Argosians garbed in their traditional "+
       "tunics are sculpted into a relief on the triangular end of the "+
       "roof of the large building.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"coop","north",0);
   add_exit(ROOM_DIR+"proad11","west",0);
   add_exit(ROOM_DIR+"croad9", "east",0);
}
