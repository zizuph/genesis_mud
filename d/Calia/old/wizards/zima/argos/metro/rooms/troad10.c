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
       "You are standing on Tetartos road before the portico of one "+
       "of the grand temples of the city to the east. The steep set "+
       "of steps and enormous pillars which front the structure implies "+
       "the dignity of temple and those inside. To the west there is "+
       "one of the buildings of the commercial district, where a sign "+
       "hangs over its entrance.\n");
   add_item("temple",
       "It is one of the grand temples of the city, its walls rising "+
       "almost to the tops of the trees. A line of massive pillars "+
       "support the portico which shades the temple's entrance, while "+
       "a set of steep steps leads up to the portico itself.\n");
   add_cmd_item("sign","read","It reads: PIESTERIO OF ARGOS.\n");
   add_item("pillars",
       "Massive pillars line the front of the temple, supporting the "+
       "roof of the portico. Each has an elaborate capitol "+
       "sculpted with doves in flight.\n");
   add_item("portico",
       "The portico is the covering over the entrance of the temple. "+
       "It is supported along its edge by a row of pillars, while set of "+
       "steps lead up onto its floor.\n");
   add_item("steps",
       "They lead up to the portico of the temple to the east.\n");
   add_item("road","It runs north and south.\n");
   add_item("building",
       "It is one of the single level, flat-roofed buildings of the "+
       "commercial district. A simple wooden sign hangs over its "+
       "entrance.\n");
   add_item(({"buildings","district","commercial district"}),
       "The buildings of the commercial district are cubic marble "+
       "structures which line the roads. The district stretches "+
       "out to the west, Tetartos road bordering it on the east.\n");
   add_item("sign",
       "It is a simple wooden sign over the door of the building "+
       "to the west. It reads: PIESTERIO OF ARGOS.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"troad9", "north",0);
   add_exit(ROOM_DIR+"troad11","south",0);
   add_exit(ROOM_DIR+"press",  "west",0);
   add_exit(PHARTEMP_DIR+"rooms/port1","steps","@@steps");
}
 
int steps() {
   write("You climb the steps of the temple up to the east.\n");
   return 0;
}
