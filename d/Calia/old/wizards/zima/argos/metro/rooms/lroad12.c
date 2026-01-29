/*
**   ARGOS - Metro - Lambdos Road
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
   set_short("Lambdos Road");
   set_long(
       "You walk down Lambdos Road between a row of public buildings "+
       "and a large temple. A set of steps lead up to the portico of "+
       "the temple to the north, while you notice an ornate sign on the "+
       "building to the south.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Lambdos road runs east and west between a temple and a row "+
       "of commercial buildings.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the south side like white cubes.\n");
   add_item("building",
        "It is one of the many shops of the commercial district. "+
        "An ornate sign hangs by the door.\n");
   add_item("sign",
        "It is a sign made of stained glass with an inscription "+
        "written on it which reads: GUALIOS GLASSCRAFTS.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. A set of steps lead up to the "+
       "temple's portico from here.\n");
   add_cmd_item("sign","read","It reads: GAULIOS GLASSCRAFTS.\n");
   add_item("portico",
       "It is a covered structure which extends from the face of "+
       "the temple, serving as an entrance to the shrine. It is "+
       "supported by a row of pillars along the front identical "+
       "to those which line the temple's walls.\n");
   add_item("pillars",
       "They support the roof of the portico, topped with capitols "+
       "sculpted with a ring of perched owls around the top.\n");
   add_item("steps",
       "They lead up to the temple's portico.\n");
 
   /* exits */
   add_exit(THEMTEMP_DIR+"rooms/port2","steps","@@steps");
   add_exit(ROOM_DIR+"glasswrk","south",0);
   add_exit(ROOM_DIR+"lroad11","west",0);
   add_exit(ROOM_DIR+"lroad13", "east",0);
}

int steps() {
   write("You climb the steps of the temple up to the north.\n");
   return 0;
}
