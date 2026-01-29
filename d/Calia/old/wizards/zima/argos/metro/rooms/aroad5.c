/*
**   ARGOS - Metro - Alpharon Road
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
       "Sunlight glints of the smooth glassy walls of the large temple "+
       "to the north, the whiteness of their marble intensifying the "+
       "reflecting sunlight. Tall columns encircle a magnificent round "+
       "structure to the south, which looks like some sort of outdoor "+
       "arena or theatre. The road continues west and east through "+
       "this rather isolated corner of the city.\n");
 
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
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"aroad4",   "west",0);
   add_exit(ROOM_DIR+"aroad6",   "east",0);
}
