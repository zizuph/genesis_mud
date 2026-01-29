/* Path through dark forest to Dephonian Temple
**
** History:
** Date        Coder       Action
** 12/14/94    Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A path through a dark forest");
   set_long(break_string(
      "You continue down a path through a dark forest of black-needled " +
      "pine trees, a light wind giving an eerie animation to the " +
      "branches. You think you hear something moving in the canopy " +
      "of the dark-barked guardians, but you can not tell what. The " +
      "path cuts through the forest to the north and southeast.\n",70));
 
    add_item(({"forest","trees"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n",70));
 
    add_item("path",
       "It looks like it has been used for decades, as well as recently.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"tdpath1","north",0);
    add_exit(ROOM_DIR+"tdpath3","southeast",0);
}
