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
       "row of commercial buildings to the south. A somewhat foul "+
       "odor wafts from the building to the south..you hope they don't "+
       "serve food. A sign hangs from a pole over the building's "+
       "entrance. "+
       "You admire the craftsmanship of a statue which stands on "+
       "a pedestal between the street and the temple.\n");
   add_item(({"road","roads","street","streets"}),
       "Lambdos road runs east and west between a temple and a row "+
       "of commercial buildings.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the south side like white cubes.\n");
   add_item("building",
       "It is one of the cubic structures which make up the "+
       "commercial district of the city. A sign has been placed "+
       "over the entrance.\n");
   add_item("sign",
       "It hangs over the entrance to the south. The lettering on it "+
       "reads: MALLINOS WOOLWORKS.\n");
   add_cmd_item("sign","read","It reads: MALLINOS WOOLWORKS.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "lined with a row of pillars. There is a statue standing on "+
       "a pedestal in front of the wall of the temple.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "sculpted with a ring of perched owls at the top.\n");
   add_item("pedestal",
       "It is a large cube of marble which serves to elevate the statue. "+
       "There is an inscription written across its face.\n");
   add_item("inscription",
       "It is sculpted into the face of the pedestal. Perhaps you can "+
       "read it.\n");
   add_cmd_item("inscription","read",
       "It reads: THEODASIA - HIEROPHANT OF THEMA.\n");
   add_item("statue",
       "It is a statue of an elderly woman with her long hair pinned "+
       "up, dressed in priestly robes which bear the emblem of an owl.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"woolwrk", "south",0);
   add_exit(ROOM_DIR+"lroad14","west",0);
   add_exit(ROOM_DIR+"lroad16","east",0);
}
