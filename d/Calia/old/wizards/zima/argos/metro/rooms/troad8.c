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
       "You are walking down Tetartos road on the eastern side of the "+
       "commercial district, your path shaded by a stand of maples which "+
       "grow along the eastern side of the road. To the west is one of "+
       "the many buildings of the commercial district, where a sign "+
       "hangs over its simple entrance.\n");
   add_item("road","It runs north and south.\n");
   add_item("building",
       "It is one of the single level, flat-roofed buildings of the "+
       "commercial district. A simple wooden sign hangs over its "+
       "entrance.\n");
   add_item(({"buildings","district","commercial district"}),
       "The buildings of the commercial district are cubic marble "+
       "structures which line the roads. The district stretches "+
       "out to the west, Tetartos road bordering it t.\n");
   add_cmd_item("sign","read","It reads: MALLINOS WOOLWORKS.\n");
   add_item("sign",
       "It is a simple wooden sign over the door of the building "+
       "to the west. It reads: MALLINOS WOOLWORKS.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"lroad16", "north",0);
   add_exit(ROOM_DIR+"troad9",  "south",0);
   add_exit(ROOM_DIR+"woolwrk", "west",0);
}
