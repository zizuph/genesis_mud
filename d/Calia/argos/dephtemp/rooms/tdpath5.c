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
      "A bit of daylight penetrates the branches of the dark " +
      "pines surrounding you, spotting the ground with patches " +
      "of light. You feel an ominous presence to the south, where " +
      "the path seems to open up into a clearing, making you think " +
      "perhaps the northeastern route might be the best option.\n",70));
 
    add_item(({"forest","trees","branches"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n",70));
 
    add_item("path",
       "It looks like it has been used for decades, as well as recently.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"tdpath4","northeast",0);
    add_exit(ROOM_DIR+"courtyrd","south",0);
}
