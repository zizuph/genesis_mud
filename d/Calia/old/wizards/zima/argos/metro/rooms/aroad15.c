/*
**   ARGOS - Metro - Alpharon road
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
       "You stand before the entrance to a long marble building with "+
       "a flat top on Alpharon road. Two pillars buttress the entrance "+
       "to the building, an inscription sculpted into the marble above "+
       "the doorway. The sweet smell of a grove of blooming cherry "+
       "trees fragrances this locality.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west along the grove of cherry trees.\n");
   add_item(({"entrance","doorway"}),
       "The entrance to the building is to the north between two pillars.\n");
   add_item("pillars",
       "They buttress the entrance to the building to the north, topped "+
       "with capitols of intricate scrollwork.\n");
   add_item("inscription",
       "Sculpted in elegant letters above the entrance of the building, "+
       "the inscription reads: SUNTECHNIA THESPIA.\n");
   add_cmd_item("inscription","read","It reads: SUNTECHNIA THESPIA.\n");
   add_item("building",
       "It is a long, flat-topped building which sits along the north "+
       "side of the road. The entrance to the building to the north is "+
       "marked by two pillars.\n");
   add_item(({"grove","trees","cherry trees","cherry grove"}),
       "A grove of cherry trees grows along the southern side of "+
       "the street, perfuming the road with their sweet scent.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"thesp1",  "north",0);
   add_exit(ROOM_DIR+"aroad14", "west",0);
   add_exit(ROOM_DIR+"aroad16", "east",0);
}
