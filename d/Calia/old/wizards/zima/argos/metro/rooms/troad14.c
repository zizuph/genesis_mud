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
       "You hear the coo of a dove from somewhere in the stand of "+
       "maples to the east as you make your way down Tetartos road. "+
       "A temple-like building sits next to the road on the west, "+
       "two pillars set into its corners. The road continues to "+
       "the north and south.\n");
 
   add_item(({"dove","coo"}),
       "You hear the song of the bird from the stand of maples to "+
       "the east, but you can't see it.\n");
   add_item(({"maples","stand","trees"}),
       "A stand of tall maples grows on the east side of the road, "+
       "their dense growth of branches and leaves screening anything "+
       "behind them.\n");
   add_item("road","It runs north and south.\n");
   add_item(({"building","temple"}),
       "It is a one-level building made of glistening marble, "+
       "though it looks to small to be a temple. The building's "+
       "wall runs between two pillars.\n");
   add_item("wall","It is a wall of sparkling white marble. It has "+
       "no ornamentation in particular.\n");
   add_item(({"pillar","pillars"}),
       "They support the walls of the building, standing on its "+
       "corners.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"troad13", "north",0);
   add_exit(ROOM_DIR+"aroad16", "south",0);
}
