/*
**   ARGOS - Metro - Alpharon and Protos roads
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
       "You continue down Alpharon road between a grove of blooming "+
       "cherry trees to the south and a large public building to the "+
       "north. This part of town seems a little deserted, though "+
       "it is peaceful and gives you a secure feeling.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west between the building and the "+
       "cherry grove.\n");
   add_item(({"structure","monument","building"}),
       "It is a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"grove","trees","cherry trees","cherry grove"}),
       "A grove of cherry trees grows along the southern side of "+
       "the street, perfuming the road with their sweet scent.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"aroad8",   "west",0);
   add_exit(ROOM_DIR+"aroad10",   "east",0);
}
