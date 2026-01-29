/*
**   ARGOS - Metro - Protos Road
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
   set_short("Protos Road");
   set_long(
       "You continue down Protos road which runs north and south "+
       "between one of the city's pillared temples to the west and "+
       "a large building on the east. A set of steps lead up to "+
       "the portico of the temple which overlooks the western side "+
       "of town.\n");
 
   add_item("building",
       "It is a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"road","roads","street","streets"}),
       "Protos road runs north and south between a temple and a large "+
       "building.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. A set of steps lead up to its "+
       "portico.\n");
   add_item("portico",
       "It is a covered structure which extends from the face of "+
       "the temple, serving as an entrance to the shrine. It is "+
       "supported by a row of pillars along the front identical "+
       "to those which line the temple's walls.\n");
   add_item("steps",
       "They lead up to the portico of the temple to the west.\n");
   add_item("pillars",
       "They support the portico of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"proad11", "north",0);
   add_exit(ROOM_DIR+"proad13", "south",0);
   add_exit(ARXTEMP_DIR+"rooms/port3","steps","@@steps");
}

int steps() {
   write("You climb the steps of the temple up to the west.\n");
   return 0;
}

