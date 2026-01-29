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
      "You continue down a winding path through a dark forest of " +
      "black pines, your skin pricked by the sharp " +
      "needles which occassionally fall from their branches. The path " +
      "continues to the north, and to the southwest where it seems "+
      "to widen.\n",70));
 
    add_item(({"forest","trees","branches"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n",70));
 
    add_item("path",
       "It looks like it has been used for decades, as well as recently.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"tdpath3","north",0);
    add_exit(ROOM_DIR+"tdpath5","southwest",0);
}
