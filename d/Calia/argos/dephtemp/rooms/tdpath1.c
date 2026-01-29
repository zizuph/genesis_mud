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
      "Black pine needles fall randomly from the surrounding towering " +
      "trees, though strangely most seem to fall directly " +
      "on you, pricking your skin. A well-trodden path leads through " +
       "the forest to the northeast and south.\n",70));
 
    add_item(({"forest","trees"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n",70));
 
    add_item("path",
       "It looks like it has been used for decades, as well as recently.\n");
 
    /* exits */
    add_exit(SWTERR_DIR+"rooms/for14","northeast",0);
    add_exit(ROOM_DIR+"tdpath2","south",0);
}
