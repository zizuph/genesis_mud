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
      "Pine cones fall from the high branches of the black pines, their "+
      "descent bouncing off limbs with small rapid crashes. Or is that "+
      "something making its way through the the forest? The narrow path "+
      "continues through the trees to the southwest and east.\n");
 
    add_item(({"forest","trees","branches"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
    add_item("sounds",
       "You don't see anything moving...you wonder what is making them.\n");
    add_item("sun",
       "You can't see it, though you can tell it is daytime.\n");
    add_item(({"cones","pine cones"}),
       "You see some hanging high from the branches of the black pines.\n");
    add_item("path",
       "It looks rather new, and leads to the southwest and east.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"npath1","southwest",0);
    add_exit(ROOM_DIR+"npath3","east",0);
}
