/*
**   ARGOS - Metro - Dueteros Road
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
   set_short("Deuteros Road");
   set_long(
       "You are standing before the entrance of a large building to "+
       "the west, above which some lettering has been sculpted into "+
       "the marble of the wall. Two blue banners "+
       "hang from poles on either side of the wide entrance, bearing "+
       "the royal arms identifying the building as property of the "+
       "crown. To the east is a tall, well-trimmed hedge which "+
       "surrounds the park of Argos. Deuteros road continues north "+
       "and south.\n");
 
   add_item("park",
       "It is surrounded with a tall well-trimmed hedge to the east. "+
       "You don't see an entrance to it here.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park. It walls the road on the east side.\n");
   add_item("building",
       "It a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. There is a wide "+
       "entrance to the building to the west. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"banner","banners"}),
       "The banners hang from a poles which angle from their bases on "+
       "the wall of the building to the west. They are made of blue "+
       "silk and bear the royal arms, a shield emblazoned with a "+
       "winged horse surmounted by a crown with three jewels.\n");
   add_item(({"road","roads","street","streets"}),
    "Deuteros road runs north and south between the building and the park.\n");
   add_item("lettering",
       "It is sculpted into the face of the building above the "+
       "entrance. Perhaps you can read it.\n");
   add_cmd_item("lettering","read",
       "The lettering reads: BIBLIOTHEKE ARGOS.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"droad12",  "north",0);
   add_exit(ROOM_DIR+"droad14",  "south",0);
   add_exit(ROOM_DIR+"libhall2", "west",0);
}
