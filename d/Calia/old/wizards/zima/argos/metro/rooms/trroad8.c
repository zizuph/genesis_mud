/*
**   ARGOS - Metro - Tritos Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Tritos Road");
   set_long(
       "You are walking down Tritos road in the commercial district "+
       "of the city. There is an entrance one of the many buildings "+
       "along the street to the west, an ornate plaque next to its "+
       "entrance. A shop is open on the east side of the street, "+
       "where a sign hangs over its doorway. Tritos continues north "+
       "and south through the city.\n");
 
   add_item(({"district","commercial district"}),
            "The commercial district is made up of rows of one-level "+
            "buildings which house the business of the city.\n");
   add_item(({"shops","establishments","buildings","enterprises"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the both sides like white cubes.\n");
   add_cmd_item("sign","read","It reads: MPROUTZOS BRASSWORKS.\n");
   add_cmd_item("plaque","read","It reads: GAULIOS GLASSCRAFTS.\n");
   add_item("building",
       "The building to the west is one of the many one-level "+
       "marble structures of the district. An ornate plaque is "+
       "hanging next to its entrance.\n");
   add_item("sign",
       "It is a simple brass sign which reads: MPROUTZOS BRASSWORKS.\n");
   add_item("entrance","It leads into the building to the west.\n");
   add_item("plaque",
      "It is an ornate plaque made of stained glass. It reads: "+
      "GAULIOS GLASSCRAFTS.\n");
   add_item("shop",
       "The shop to the west is one of the many one-level "+
       "marble structures of the district. A sign hangs over its "+
       "doorway.\n");
   add_item("doorway","It leads into the shop to the east.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"lroad13","north",0);
   add_exit(ROOM_DIR+"trroad9","south",0);
   add_exit(ROOM_DIR+"brasswrk", "east",0);
   add_exit(ROOM_DIR+"glasswrk", "west",0);
}
