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
       "Two of the city's monuments line Protos road as you continue "+
       "down its path, a temple to the west and a large public building "+
       "to the east. This part of town seems a bit quieter than the "+
       "rest, giving you a momentarily relaxed feeling.\n");
 
   add_item("building",
       "It is a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"road","roads","street","streets"}),
       "Protos road runs north and south between a temple and the large "+
       "building.\n");
 
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. You don't seen an entrance to it "+
       "anywhere around here.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"proad13", "north",0);
   add_exit(ROOM_DIR+"aroad7",  "south",0);
}
