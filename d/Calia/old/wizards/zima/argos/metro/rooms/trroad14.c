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
       "You notice a relief sculpted on the temple-like building "+
       "to the east as you walk along Tritos road, paralleled by "+
       "the hedge of the park on the west side. Two pillars are "+
       "set at the corners of the one story building, to which you "+
       "see no entrance anywhere. Tritos road continues north and "+
       "south.\n");
   add_item("park",
       "It is surrounded with a well-trimmed hedge which walls the "+
       "road on the west side. You see no entrance to it here.\n");
   add_item("road","It runs north and south.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
   add_item(({"building","temple"}),
       "The building is adorned much like one of the city's temples, "+
       "but it is much too small to house one of the religious orders "+
       "known to exist here. A thick pillar is set on each corner of "+
       "the building, while a relief has been sculped into its wall.\n");
   add_item("relief",
       "Sculpted into the wall of the building, it is the likeness of "+
       "a beautiful woman wearing a long flowing robe, belted at the "+
       "waist. She wears a small crown with three jewels on her head "+
       "and holds an actor's mask in her hand.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"trroad13","north",0);
   add_exit(ROOM_DIR+"aroad13","south",0);
}
