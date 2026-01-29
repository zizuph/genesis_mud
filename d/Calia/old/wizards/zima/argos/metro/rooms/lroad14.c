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
       "You are walking down Lambdos road along the northern edge "+
       "of the city's commercial district. Tall pillars rise like "+
       "trees along the walls of a large temple to the north, while "+
       "you notice a brass sign bolted to the marble wall of the "+
       "shop to the south.\n");
 
   add_item("shop",
       "It is one of the many cubic marble buildings of the business "+
       "district. There is a brass sign bolted on its wall near the "+
       "entrance.\n");
   add_item("sign",
       "It is a sign made of brass cast with letters on it which read: "+
       "MPROUTZOS BRASSWORKS.\n");
   add_item(({"road","roads","street","streets"}),
       "Lambdos road runs east and west between a temple and a row "+
       "of commercial buildings.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the south side like white cubes.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. You see some steps leading up "+
       "to the temple further west.\n");
   add_cmd_item("sign","read","It reads: MPROUTZOS BRASSWORKS.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "sculpted with a ring of perched owls at the top.\n");
   add_item("steps",
       "They seem to lead up into the temple further west.");
 
   /* exits */
   add_exit(ROOM_DIR+"brasswrk", "south",0);
   add_exit(ROOM_DIR+"lroad13","west",0);
   add_exit(ROOM_DIR+"lroad15","east",0);
}

