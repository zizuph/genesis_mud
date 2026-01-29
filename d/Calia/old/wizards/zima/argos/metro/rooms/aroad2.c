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
       "You are near the west end of Alpharon Road in the city of Argos, "+
       "which runs along the high walls of a massive temple on the north "+
       "side. To the southeast sits a large circular structure, its "+
       "walls encircled by two levels of tall thin columns. The road "+
       "continues west and east.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west along the south side of town.\n");
   add_item(({"structure","circular structure"}),
       "It is an enormous circular building, which seems to have no "+
       "walls except two levels of columns which ring around it. "+
       "The building also seems to have no roof, so it is probably "+
       "some sort of outdoor theatre or arena.\n");
   add_item("columns",
       "They are closely set together in two levels of rings to form "+
       "the wall of the structure to the south.\n");
   add_item("temple",
      "It is a massive structure of white marble, its high walls buttressed "+
      "by tall pillars.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"aroad1",   "west",0);
   add_exit(ROOM_DIR+"aroad3",   "east",0);
}
