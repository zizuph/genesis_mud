/*
**   ARGOS - Metro - Lambdos road
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
   set_short("Lambdos Road");
   set_long(
       "You are standing on Lambdos road on the north side of town, "+
       "between the corner of a large temple to the north and a "+
       "row of commercial buildings to the south. The familiar "+
       "smell of alcohol wafts from the entrance of the building "+
       "to the south, carried with the sounds of jovial compatriots. "+
       "You admire the craftsmanship of a statue which stands on a "+
       "large pedestal between the street and the temple.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Lambdos road runs east and west between a temple and a row "+
       "of commercial buildings.\n");
   add_cmd_item("sign","read","It reads: OUZOPHILOS PUB.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the south side like white cubes.\n");
   add_item("building",
       "It is one of the cubic structures which make up the "+
       "commercial district of the city. A sign has been placed "+
       "over the entrance.\n");
   add_item("sign",
       "It hangs over the entrance to the south. The lettering on it "+
       "reads: OUZOPHILOS PUB.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "lined with a row of pillars. A statue stands on a pedestal "+
       "between here and the temple's wall.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "sculpted with a ring of perched owls at the top.\n");
   add_item("pedestal",
       "It is a cube of white marble which serves to elevate the statue. "+
       "There is an inscription written across its face.\n");
   add_item("inscription",
       "It is sculpted into the face of the pedestal. Perhaps you can "+
       "read it.\n");
   add_cmd_item("inscription","read",
       "It reads: THULTRIA - HIEROPHANT OF THEMA.\n");
   add_item("statue",
       "It is a statue of a young woman dressed in a long robe "+
       "belted with a twisted rope. She holds a tall staff in one "+
       "hand upon which an owl is perched.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"pub","south",0);
   add_exit(ROOM_DIR+"lroad8","west",0);
   add_exit(ROOM_DIR+"lroad10","east",0);
}
