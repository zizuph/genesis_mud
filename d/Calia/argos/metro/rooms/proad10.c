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
       "You are standing on Protos road on the west side of Argos. "+
       "A set of steps lead up to the portico of one "+
       "of the city's temples to the west, a sharp climb up to the "+
       "face of the shrine. A unique sign hangs above the entrance "+
       "to the establishment to the east, one of the cubic marble "+
       "buildings which line the street. Protos road continues "+
       "north and south between the commercial district and the "+
       "front of the temple.\n");
 
   add_item(({"building","shop","establishment"}),
       "It is one of the buildings of the commercial district, a "+
       "simple cube of marble. You notice a slight stench wafting "+
       "from within. A unique sign hangs over its entrance to the east.\n");
   add_item("sign",
       "The wooden sign is carved in the shape of a pigeon. There is no "+
       "lettering on it, but the details of the fowl are colorfully "+
       "painted.\n");
   add_cmd_item("sign","read","There is nothing on the sign to read.\n");
   add_item(({"road","roads","street","streets"}),
       "Protos road runs north and south between a temple and a row "+
       "of commercial buildings.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the east side like white cubes.\n");
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
   add_exit(ROOM_DIR+"proad9", "north",0);
   add_exit(ROOM_DIR+"proad11", "south",0);
   add_exit(ROOM_DIR+"coop", "east",0);
   add_exit(ARXTEMP_DIR+"rooms/port1","steps","@@steps");
 
}
 
int steps() {
   write("You climb the steps of the temple up to the west.\n");
   return 0;
}
