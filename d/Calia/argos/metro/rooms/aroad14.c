/*
**   ARGOS - Metro - Alpharon and Tritos roads
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/30/95    Zima       Created
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
       "The artwork of a relief sculpted into the wall of the building "+
       "to the north catches your attention as you stroll down Alpharon "+
       "road. You barely notice the aroma and beauty of the grove of "+
       "cherry trees which line the road on the south side.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west along the grove of cherry trees.\n");
   add_item("building",
       "It is a long, flat-topped building which sits along the north "+
       "side of the road. Their is an interesting relief sculpted into "+
       "its wall.\n");
   add_item(({"relief","wall"}),
       "The relief sculpted into the wall of the building is that of "+
       "two carnival-type masks, one with a smiling face and the other "+
       "with a sad look of despair.\n");
   add_item(({"grove","trees","cherry trees","cherry grove"}),
       "A grove of cherry trees grows along the southern side of "+
       "the street, perfuming the road with their sweet scent.\n");
 
   /* exits */
    add_exit(ROOM_DIR+"aroad13","west",0);
   add_exit(ROOM_DIR+"aroad15","east",0);
}
