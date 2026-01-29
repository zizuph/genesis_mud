/*
**   ARGOS - Metro - Tetartos Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/14/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Tetartos Road");
   set_long(
       "A set of steps leads up to the portico of one of the city's "+
       "grand temples to the east. The face of the temple ends here, "+
       "giving way to a stand of maples further south down the road. "+
       "The high columns of the Amphitheatre rise along the western "+
       "side of the road, which runs to the north and south.\n");
 
   add_item("temple",
       "It is one of the grand temples of the city, its walls rising "+
       "almost to the tops of the trees. A line of massive pillars "+
       "support the portico which shades the temple's entrance, while "+
       "a set of steep steps leads up to the portico itself.\n");
   add_item("pillars",
       "Massive pillars line the front of the temple, supporting the "+
       "roof of the portico. Elaborate capitols are sculpted with the "+
       "likeness of maple leaves.\n");
   add_item("portico",
       "The portico is the covering over the entrance of the temple. "+
       "It is supported along its edge by a row of pillars, while set of "+
       "steps lead up onto its floor.\n");
   add_item("steps",
       "They lead up to the portico of the temple to the east.\n");
   add_item(({"maples","stand","trees"}),
       "A stand of tall maples grows on the east side of the road, "+
       "starting just south of the southern end of the portico of the "+
       "temple.\n");
   add_item("road","It runs north and south.\n");
 
   add_item(({"amphitheatre","Amphitheatre"}),
       "It is an outdoor area where dramatic and comic presentations "+
       "are performed. It framed by a row of high columns. You don't see "+
       "an entrance into the amphitheatre through the columns here.\n");
   add_item("columns",
       "The columns rise high into the air, their capitols sculpted "+
       "with the images of actor's masks. They stand independently "+
       "around the Amphitheatre, paralleling the road to the north.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"troad11", "north",0);
   add_exit(ROOM_DIR+"troad13", "south",0);
   add_exit(PHARTEMP_DIR+"rooms/port3","steps","@@steps");
}
 
int steps() {
   write("You climb the steps of the temple up to the east.\n");
   return 0;
}
