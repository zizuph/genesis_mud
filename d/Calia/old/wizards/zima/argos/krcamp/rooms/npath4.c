/* Northern Path through dark forest around Kretan Camp
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 12/2/95     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A path through a dark forest");
   set_long(
      "A sharp pine smell wafts from the black pines of the "+
      "forest, as if decay has set in on some of the dark giants. "+
      "The branches of the tall pines block the sun from above, their "+
      "canopy forming a roof for the forest floor.\n");
 
    add_item(({"forest","trees","branches","pine","pines"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
    add_item("sounds",
       "You don't see anything moving...you wonder what is making them.\n");
    add_item(({"air","smell"}),
       "It is a punguent smell coming from the trees.\n");
    add_cmd_item(({"pines","pine","trees","air","smell"}), "smell",
       "Your nostrils are filled with a sharp odor.\n");
    add_item("sun",
       "You can't see it, though you can tell it is daytime.\n");
    add_item(({"cones","pine cones"}),
       "You see some hanging high from the branches of the black pines.\n");
    add_item("path",
       "It looks rather new, and leads to the west and east.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"npath3","west",0);
    add_exit(ROOM_DIR+"npath5","east",0);
}
