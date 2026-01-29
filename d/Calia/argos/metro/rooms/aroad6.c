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
       "You are walking down Alpharon Road on the southwestern side of "+
       "town. You see the corner of one of the grand temples of the city "+
       "a little further west, while a round structure encircled by "+
       "close-set columns sits across a courtyard to the south.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west along the south side of town.\n");
   add_item(({"structure","circular structure"}),
       "It is an enormous circular building, which seems to have no "+
       "walls except two levels of columns which ring around it. "+
       "The building also seems to have no roof, so it is probably "+
       "some sort of outdoor theatre or arena.\n");
   add_item("courtyard",
       "It is a grassy area before the entrance to the columned structure "+
       "to the south. You see a tall statue in the middle of it, and an "+
       "entrance to it further east.\n");
   add_item("statue",
       "It is in the middle of the courtyard to the south. You can't make "+
       "out any of its features from this distance.\n");
   add_item("columns",
       "They are closely set together in two levels of rings to form "+
       "the wall of the structure to the southwest.\n");
   add_item("temple",
      "It is a massive structure of white marble, its high walls buttressed "+
      "by tall pillars.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"aroad5",   "west",0);
   add_exit(ROOM_DIR+"aroad7",   "east",0);
}
