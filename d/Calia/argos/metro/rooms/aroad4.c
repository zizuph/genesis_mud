/*
**   ARGOS - Metro - Alpharon road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   11/12/95   Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Alpharon Road");
   set_long(
       "A gentle breeze whistles between the temple to the north and "+
       "the round columned structure to the south, carrying the smell of "+
       "a nearby forest. Alpharon road continues to the west and east "+
       "along its quiet path.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west along the south side of town.\n");
   add_item(({"structure","circular structure"}),
       "It is an enormous circular building, which seems to have no "+
       "walls except two levels of columns which ring around it. "+
       "The building also seems to have no roof, so it is probably "+
       "some sort of outdoor theatre or arena.\n");
   add_item("columns",
       "They are closely set together in two levels of rings to form "+
       "the wall of the structure to the southwest.\n");
   add_item("temple",
      "It is a massive structure of white marble, its high walls buttressed "+
      "by tall pillars.\n");
   add_item("forest",
      "You can't see it, but you get a wiff of its dark pine scent.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"aroad3",   "west",0);
   add_exit(ROOM_DIR+"aroad5",   "east",0);
}
